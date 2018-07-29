//
// Created by Александр Баташев on 25.05.2018.
//

//#include <stack>
#include <stdexcept>
#include "Session.h"
#include <tuple>

void athena::core::Session::prepare ( athena::core::Node* logits ) {

    if ( logits != nullptr ) {
        logits->setPersistResult();
        auto[bytecode, shape, resultCell] = getByteCode( logits );
        this->bytecode.clear();
        this->bytecode.insert(
                std::end( this->bytecode ), std::begin( bytecode ),
                std::end( bytecode ));
        this->resultCell = resultCell;
        this->resultShape = *shape;
    }
}

std::tuple< std::vector< vm_word >, athena::core::TensorShape*, vm_word >
athena::core::Session::getByteCode ( Node* logits ) {

    std::vector< vm_word > curBC;
    vm_word resultCell = 0;
    TensorShape * resultShape;

    if ( logits->isInputNode()) {
        auto inpNode = dynamic_cast<InputNode*>(logits);
        resultShape = new TensorShape(inpNode->getData()->getShape());
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
            std::vector< TensorShape > predShapes;
            for (
                Node* pred : logits->getIncomingNodes()) {
                if ( pred->isCalculated()) {
                    resCells.push_back( pred->getResult());
                    pred->updateUsageCount();
                    if ( pred->isGarbage()) {
                        virtualMemory->free( pred->getResult());
                        curBC.push_back( static_cast<vm_word>( OpCode::DEL ));
                        curBC.push_back( pred->getResult());
                    }
                } else {
                    auto[predBC, predShape, predResCell] = getByteCode( pred );
                    curBC.insert(
                            std::end( curBC ), std::begin( predBC ),
                            std::end( predBC ));
                    resCells.push_back( predResCell );
                    predShapes.push_back( *predShape );
                }
            }

            resultShape = new TensorShape(logits->getOp()->getOutputShape( predShapes ));
            auto resultTensor = new Tensor( *resultShape, DataType::FLOAT ); // todo TYPE
            resultCell = virtualMemory->allocate( resultTensor );

            curBC.push_back( static_cast<vm_word>( OpCode::ALLOC ));
            curBC.push_back( resultShape->dimensions());
            for ( unsigned int d = 0; d < resultShape->dimensions(); d++ ) {
                curBC.push_back( resultShape->dim( d ));
            }
            curBC.push_back( resultCell );

            std::vector< vm_word > op_bytecode = logits->getOp()->getOpBytecode(
                    resCells, resultCell
            );
            curBC.insert(
                    std::end( curBC ), std::begin( op_bytecode ),
                    std::end( op_bytecode ));

            for ( int i = 0; i < logits->getIncomingNodes().size(); i++ ) {
                auto derivShape = logits->getOp()->getDerivativeShape( i, predShapes );
                auto derivTensor = new Tensor( derivShape, DataType::FLOAT ); // todo type
                vm_word derivCell = virtualMemory->allocate( derivTensor );

                curBC.push_back( static_cast<vm_word>( OpCode::ALLOC ));
                curBC.push_back( derivShape.dimensions());
                for ( unsigned int d = 0; d < derivShape.dimensions(); d++ ) {
                    curBC.push_back( derivShape.dim( d ));
                }
                curBC.push_back( derivCell );

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

    for ( InputNode* node : headNodes ) {
        node->getInitializer()->initialize(
                executor->getMemoryManager(),
                node->getData());
    }

    executor->setBytecode( bytecode );
    executor->execute();
    return executor->getMemoryManager()->getTensor( resultCell );
}

unsigned long athena::core::Session::getResultCell () {
    return resultCell;
}

void athena::core::Session::setExecutor ( athena::backend::AbstractExecutor* exec ) {
    this->executor = exec;
}

athena::backend::VirtualMemory* athena::core::Session::getMemory () {
    return virtualMemory;
}

athena::backend::AbstractExecutor* athena::core::Session::getExecutor () {
    return executor;
}
