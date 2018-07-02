//
// Created by Александр Баташев on 25.05.2018.
//

#include <stack>
#include <stdexcept>
#include "Session.h"
#include <tuple>

void athena::core::Session::prepare ( athena::core::Node* logits ){

    if ( logits != nullptr ) {
        auto[bytecode, resultCell] = getByteCode ( logits );
        this->bytecode.clear ();
        this->bytecode.insert (
                std::end ( this->bytecode ), std::begin ( bytecode ),
                std::end ( bytecode ));
        this->resultCell = resultCell;
    }

    executorService = new athena::backend::ExecutorService (
            bytecode, maxMemSize,
            resultCell
    );
}

std::tuple< std::vector< vm_word >, vm_word >
athena::core::Session::getByteCode ( Node* logits ){

    std::vector< vm_word > curBC;
    vm_word resultCell = 0;

    if ( logits->isInputNode ()) {
        auto inpNode = dynamic_cast<InputNode*>(logits);
        resultCell = getFreeMemCell ();
        inpNode->setMappedMemCell ( resultCell );
        headNodes.push_back ( inpNode );
    } else {
        if ( logits->getOp ()->getOperandsCount () !=
             logits->getIncomingNodes ().size ()) {
            throw std::runtime_error (
                    "Wrong count of arguments at " + logits->getName () + ". Expected " +
                    std::to_string ( logits->getOp ()->getOperandsCount ()) + ", got " +
                    std::to_string ( logits->getIncomingNodes ().size ()));
        } else {

            // todo check shape compatibility
            std::vector< vm_word > resCells;
            for (
                Node* pred : logits->getIncomingNodes ()) {
                if ( pred->isCalculated ()) {
                    resCells.push_back ( pred->getResult ());
                    pred->updateUsageCount ();
                    if ( pred->isGarbage ()) {
                        free_mem.push ( pred->getResult ());
                    }
                } else {
                    auto[predBC, predResCell] = getByteCode ( pred );
                    curBC.insert (
                            std::end ( curBC ), std::begin ( predBC ),
                            std::end ( predBC ));
                    resCells.push_back ( predResCell );
                }
            }

            resultCell = getFreeMemCell ();
            std::vector< vm_word > op_bytecode = logits->getOp ()->getOpBytecode (
                    resCells, resultCell
            );
            curBC.insert (
                    std::end ( curBC ), std::begin ( op_bytecode ),
                    std::end ( op_bytecode ));

            for (
                    int i = 0; i < logits->getIncomingNodes ().size (); i++
                    ) {
                vm_word derivCell = getFreeMemCell ();
                std::vector< vm_word > deriv_bytecode =
                        logits->getOp ()->getDerivativeBytecode (
                                i, resCells, derivCell
                        );
                logits->addDerivative ( derivCell );
                curBC.insert (
                        std::end ( curBC ),
                        std::begin ( deriv_bytecode ),
                        std::end ( deriv_bytecode ));
            }

            logits->setCalculated ( resultCell );

        }
    }

    return std::make_tuple ( curBC, resultCell );
}

unsigned long athena::core::Session::getFreeMemCell (){
    unsigned long res;
    if ( !free_mem.empty ()) {
        res = free_mem.top ();
        free_mem.pop ();
        memory_map[ res ] = true;
    } else {
        res = static_cast<int>(memory_map.size ());
        memory_map.push_back ( true );
        if ( memory_map.size () > maxMemSize ) {
            maxMemSize = static_cast<int>(memory_map.size ());
        }
    }


    return res;
}

athena::core::Tensor* athena::core::Session::run (){
    // todo implement a better solution
    for (
        InputNode* node : headNodes
            ) {
        executorService->setMemoryCell ( node->getMappedMemCell (), node->getData ());
    }

    return executorService->execute ();
}

unsigned long athena::core::Session::getResultCell (){
    return resultCell;
}
