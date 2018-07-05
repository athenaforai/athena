//
// Created by Александр Баташев on 28.06.2018.
//

#include <queue>
#include <tuple>
#include "GradientDescent.h"

athena::core::optimizers::GradientDescent::GradientDescent (
        AbstractLossFunction* loss, float learningRate
)
        : AbstractOptimizer( loss ), learningRate( learningRate ) {}


void athena::core::optimizers::GradientDescent::prepare () {

    if ( loss != nullptr ) {
        auto[bytecode, resultCell] = getByteCode( loss );
        this->bytecode.clear();
        this->bytecode.insert(
                std::end( this->bytecode ), std::begin( bytecode ),
                std::end( bytecode ));
    }

}

std::tuple< std::vector< unsigned long >, unsigned long >
athena::core::optimizers::GradientDescent::getByteCode ( AbstractLossFunction* node ) {

    std::vector< vm_word > bytecode;

    vm_word errorCell = this->session->getFreeMemCell();
    std::vector< vm_word > lossArgs( 1 );
    lossArgs.push_back( lastResultCell );
    node->getOp()->getOpBytecode( lossArgs, errorCell );

    std::queue< Node* > nodesQueue;
    nodesQueue.push( node->getIncomingNodes()[ 0 ] );
    std::queue< vm_word > errorCells;
    errorCells.push( errorCell );

    while ( !nodesQueue.empty()) {
        Node* curNode = nodesQueue.front();
        nodesQueue.pop();

        for (
                int i = 0; i < curNode->getIncomingNodes().size(); i++
                ) {
            Node* inNode = curNode->getIncomingNodes()[ i ];
            vm_word err = errorCells.front();
            errorCells.pop();

            vm_word newErr = session->getFreeMemCell();

            bytecode.push_back( static_cast<vm_word>(OpCode::MATMUL));
            bytecode.push_back( 0 );
            bytecode.push_back( err );
            bytecode.push_back( 0 );
            bytecode.push_back( curNode->getDerivative( i ));
            bytecode.push_back( newErr );

            errorCells.push( newErr );

            if ( inNode->isInputNode()) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
                auto inputNode = dynamic_cast<InputNode*>(inNode);
                if ( !inputNode->isFrozen()) {
                    bytecode.push_back( static_cast<vm_word>(OpCode::SCALE));
                    vm_word* tmp;
                    float alpha = -1 * learningRate;
                    tmp = reinterpret_cast<vm_word*>(&alpha);
                    bytecode.push_back( *tmp );
                    bytecode.push_back( newErr );
                    vm_word delta = session->getFreeMemCell();
                    bytecode.push_back( delta );

                    bytecode.push_back( static_cast<vm_word>(OpCode::ADD));
                    bytecode.push_back( inputNode->getMappedMemCell());
                    bytecode.push_back( delta );
                    bytecode.push_back( inputNode->getMappedMemCell());
                }
#pragma clang diagnostic pop
            } else {
                nodesQueue.push( inNode );
            }
        }

        /*
         * todo:
         * for every incoming node
         * 1) Pop error from errorCells
         * 2) Multiply error cell by corresponding derivative of curNode
         * 3) Push result back to queue
         * 4) If current incoming node is InputNode and it is not frozen, update values
         * 5) Else push current incoming node to queue
         */
    }

    return std::make_tuple( bytecode, static_cast<unsigned long>(0));
}
