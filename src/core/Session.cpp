//
// Created by Александр Баташев on 25.05.2018.
//

#include <stack>
#include <stdexcept>
#include "Session.h"
#include <tuple>

void athena::core::Session::prepare ( athena::core::Node* logits ) {

    if ( logits != nullptr ) {
        auto[bytecode, shape, resultCell] = getByteCode( logits );
        this->bytecode.clear();
        this->bytecode.insert(
                std::end( this->bytecode ), std::begin( bytecode ),
                std::end( bytecode ));
        this->resultCell = resultCell;
        this->resultShape = resultShape;
    }

//    executorService = new athena::backend::ExecutorService(
//            bytecode, maxMemSize,
//            resultCell
//    );
}

std::tuple< std::vector< vm_word >, athena::core::TensorShape , vm_word >
athena::core::Session::getByteCode ( Node* logits ) {

    std::vector< vm_word > curBC;
    vm_word resultCell = 0;
    TensorShape resultShape;

    if ( logits->isInputNode()) {
        auto inpNode = dynamic_cast<InputNode*>(logits);
        resultShape = inpNode->getData()->getShape();
        resultCell = virtualMemory->allocate( inpNode->getData());
        inpNode->setMappedMemCell( resultCell );
        headNodes.push_back( inpNode );
    } else {
        if ( logits->getOp()->getOperandsCount() !=
             logits->getIncomingNodes().size()) {
            throw std::runtime_error(
                    "Wrong count of arguments at " + logits->getName() + ". Expected " +
                    std::to_string( logits->getOp()->getOperandsCount()) + ", got " +
                    std::to_string( logits->getIncomingNodes().size()));
        } else {

            // todo check shape compatibility
            std::vector< vm_word > resCells;
            std::vector< TensorShape & > predShapes;
            for (
                Node* pred : logits->getIncomingNodes()) {
                if ( pred->isCalculated()) {
                    resCells.push_back( pred->getResult());
                    pred->updateUsageCount();
                    if ( pred->isGarbage()) {
                        virtualMemory->free( pred->getResult());
                    }
                } else {
                    auto[predBC, predShape, predResCell] = getByteCode( pred );
                    curBC.insert(
                            std::end( curBC ), std::begin( predBC ),
                            std::end( predBC ));
                    resCells.push_back( predResCell );
                    predShapes.push_back( predShape );
                }
            }

            resultShape = logits->getOp()->getOutputShape( predShapes );
            auto resultTensor = new Tensor( resultShape, DataType::FLOAT ); // todo TYPE
            resultCell = virtualMemory->allocate( resultTensor );
            std::vector< vm_word > op_bytecode = logits->getOp()->getOpBytecode(
                    resCells, resultCell
            );
            curBC.insert(
                    std::end( curBC ), std::begin( op_bytecode ),
                    std::end( op_bytecode ));

            for ( int i = 0; i < logits->getIncomingNodes().size(); i++ ) {
//                vm_word derivCell = getFreeMemCell();
                auto derivShape = logits->getOp()->getDerivativeShape( i, predShapes );
                auto derivTensor = new Tensor( derivShape, DataType::FLOAT ); // todo type
                vm_word derivCell = virtualMemory->allocate( derivTensor );
                std::vector< vm_word > deriv_bytecode =
                        logits->getOp()->getDerivativeBytecode(
                                i, resCells, derivCell
                        );
                logits->addDerivative( derivCell );
                curBC.insert(
                        std::end( curBC ),
                        std::begin( deriv_bytecode ),
                        std::end( deriv_bytecode ));
            }

            logits->setCalculated( resultCell );

        }
    }

    return std::make_tuple( curBC, resultShape, resultCell );
}

athena::core::Tensor* athena::core::Session::run () {
    // todo implement a better solution
//    for (
//        InputNode* node : headNodes
//            ) {
//        executorService->setMemoryCell( node->getMappedMemCell(), node->getData());
//    }
//
//    executorService->setBytecode( bytecode );
//
//    return executorService->execute();
    executor->execute();
//    executor->getMemoryManager()->
    return nullptr;
}

unsigned long athena::core::Session::getResultCell () {
    return resultCell;
}

void athena::core::Session::setExecutor ( athena::backend::AbstractExecutor* exec ) {
    this->executor = exec;
}

//athena::backend::ExecutorService* athena::core::Session::getExecutorService () {
//    return executorService;
//}
