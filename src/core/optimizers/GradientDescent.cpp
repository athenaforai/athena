//
// Created by Александр Баташев on 28.06.2018.
//

#include <queue>
#include <tuple>
#include "GradientDescent.h"

athena::core::optimizers::GradientDescent::GradientDescent (
        athena::core::loss::AbstractLossFunction* loss, float learningRate
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
athena::core::optimizers::GradientDescent::getByteCode (
        athena::core::loss::AbstractLossFunction* node ) {

    /*
     * todo:
     * for every incoming node
     * 1) Pop error from errorCells
     * 2) Multiply error cell by corresponding derivative of curNode
     * 3) Push result back to queue
     * 4) If current incoming node is InputNode and it is not frozen, update values
     * 5) Else push current incoming node to queue
     */

    std::vector< vm_word > bytecode;

    /*
     * The whole algorithm:
     * 1. Calculate actual error E
     * 2. Let's Q - queue of nodes, EQ - queue of errors
     * 2.1 node -> Q
     * 2.2 E -> EQ
     * 3. For each node N in Q
     * 3.1 E = EQ.top()
     * 3.2 If this is variable node, adjust weights: N = N - alpha * E
     * 3.3 If this is regular node, for each incoming node I:
     * 3.3.1 If I is constant, skip
     * 3.3.2 Ei = Di (*) E, where Ei is the new error value, Di - derivative of N
     * with respect to I, (*) - Hadamard (elementwise) product.
     * 3.3.3 Ei -> EQ
     * 3.3.4 I -> Q
     */

    // 1.
    auto lastRes = session->getMemory()->getTensor( session->getResultCell());

    // todo at the moment loss is always scalar
    auto lossShape = TensorShape( { 1 } );

    auto lossTensor = new Tensor( lossShape, lastRes->getType());
    session->getMemory()->allocate( lossTensor );

    bytecode.push_back( static_cast<vm_word>(OpCode::ALLOC));
    bytecode.push_back( lossShape.dimensions());
    bytecode.push_back( 1 ); // todo update
    bytecode.push_back( lossTensor->getStartAddress());

    std::vector< vm_word > lossArgs;
    auto label = dynamic_cast<InputNode*>(node->getIncomingNodes()[ 1 ]);
    session->getMemory()->allocate( label->getData());

    lossArgs.push_back( lastRes->getStartAddress());
    lossArgs.push_back( label->getData()->getStartAddress());

    auto lossBytecode =
            node->getOp()->getOpBytecode( lossArgs, lossTensor->getStartAddress());

    bytecode.insert( std::end( bytecode ), std::begin( lossBytecode ),
                     std::end( lossBytecode ));

    // todo calculate derivative

    std::vector< TensorShape > tmp;
    tmp.push_back( lastRes->getShape());
    tmp.push_back( lossTensor->getShape());
    auto lossDerivativeShape = node->getOp()->getDerivativeShape( 0, tmp );

    auto lossDerivativeTensor = new Tensor( lossDerivativeShape, lastRes->getType());

    session->getMemory()->allocate( lossDerivativeTensor );

    bytecode.push_back( static_cast<vm_word>(OpCode::ALLOC));
    bytecode.push_back( lossDerivativeShape.dimensions());
    for ( unsigned long i = 0; i < lossDerivativeShape.dimensions(); i++ ) {
        bytecode.push_back( lossDerivativeShape.dim( i ));
    }
    bytecode.push_back( lossDerivativeTensor->getStartAddress());

    auto lossDerivativeBytecode = node->getOp()->getDerivativeBytecode(
            0, lossArgs,
            lossDerivativeTensor->getStartAddress());

    bytecode.insert( std::end( bytecode ), std::begin( lossDerivativeBytecode ),
                     std::end( lossDerivativeBytecode ));

    node->addDerivative( lossDerivativeTensor->getStartAddress());

    // 2.

    std::queue< Node* > nodesQueue;
    std::queue< Tensor* > errorsQueue;

    nodesQueue.push( node );
    errorsQueue.push( lossTensor );

    // create tensor for alpha value
    TensorShape alphaShape( { 1 } );
    // todo type
    auto alphaTensor = new Tensor( alphaShape, DataType::FLOAT );

    session->getMemory()->allocate( alphaTensor );

    bytecode.push_back( static_cast<vm_word>(OpCode::ALLOC));
    bytecode.push_back( 1 );
    bytecode.push_back( 1 );
    bytecode.push_back( alphaTensor->getStartAddress());

    bytecode.push_back( static_cast<vm_word>(OpCode::MKSCALAR));
    auto *mlr = new float[1];
    mlr[0] = -learningRate;
    vm_word a = *reinterpret_cast<vm_word*>(mlr);
    bytecode.push_back( a );
    bytecode.push_back( alphaTensor->getStartAddress());


    // 3.

    while ( !nodesQueue.empty()) {
        Node* n = nodesQueue.front();
        nodesQueue.pop();

        auto error = errorsQueue.front();
        errorsQueue.pop();

        if ( n->isInputNode()) {
            auto inN = dynamic_cast<InputNode*>(n);
            auto scaledErrorTensor = new Tensor( error->getShape(), error->getType());
            session->getMemory()->allocate( scaledErrorTensor );

            bytecode.push_back( static_cast<vm_word>(OpCode::ALLOC));
            bytecode.push_back( scaledErrorTensor->getShape().dimensions());
            for ( unsigned long i = 0; i < scaledErrorTensor->getShape().dimensions();
                  i++ ) {
                bytecode.push_back( scaledErrorTensor->getShape().dim( i ));
            }
            bytecode.push_back( scaledErrorTensor->getStartAddress());

            bytecode.push_back( static_cast<vm_word>(OpCode::SCALE));
            bytecode.push_back( alphaTensor->getStartAddress());
            bytecode.push_back( error->getStartAddress());
            bytecode.push_back( scaledErrorTensor->getStartAddress());

            bytecode.push_back( static_cast<vm_word>(OpCode::ADD));
            bytecode.push_back( inN->getData()->getStartAddress());
            bytecode.push_back( scaledErrorTensor->getStartAddress());
            bytecode.push_back( inN->getData()->getStartAddress());

            bytecode.push_back( static_cast<vm_word>(OpCode::DEL));
            bytecode.push_back( scaledErrorTensor->getStartAddress());
        } else {

            for ( unsigned long i = 0; i < n->getIncomingNodes().size(); i++ ) {

                Node* incomingNode = n->getIncomingNodes()[ i ];

                if ( incomingNode->isInputNode()) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
                    auto inN = dynamic_cast<InputNode*>(incomingNode);
#pragma clang diagnostic pop
                    if ( inN->isFrozen()) {
                        continue; // skip constants
                    }
                }

                vm_word inDerivTensorAddress = node->getDerivative( i );

                auto newErrTensor = new Tensor( error->getShape(), error->getType());
                session->getMemory()->allocate( newErrTensor );

                bytecode.push_back( static_cast<vm_word>(OpCode::ALLOC));
                bytecode.push_back( newErrTensor->getShape().dimensions());
                for ( unsigned long j = 0;
                      j < newErrTensor->getShape().dimensions(); j++ ) {
                    bytecode.push_back( newErrTensor->getShape().dim( j ));
                }
                bytecode.push_back( newErrTensor->getStartAddress());

                if ( error->getShape().dimensions() == 1 &&
                     error->getShape().dim( 0 ) == 1 ) {
                    bytecode.push_back( static_cast<vm_word>(OpCode::SCALE));
                } else {
                    bytecode.push_back( static_cast<vm_word>(OpCode::HADAMARD));
                }

                bytecode.push_back( error->getStartAddress());
                bytecode.push_back( inDerivTensorAddress );
                bytecode.push_back( newErrTensor->getStartAddress());

                errorsQueue.push( newErrTensor );
                nodesQueue.push( incomingNode );

            }

        }

        bytecode.push_back( static_cast<vm_word>(OpCode::DEL));
        bytecode.push_back( error->getStartAddress());
    }

    return std::make_tuple( bytecode, static_cast<unsigned long>(0));
}

void athena::core::optimizers::GradientDescent::minimize () {

    auto label = dynamic_cast<InputNode*>(loss->getIncomingNodes()[ 1 ]);

    label->getInitializer()->initialize( session->getExecutor()->getMemoryManager(),
                                         label->getData());

    session->getExecutor()->setBytecode( bytecode );
    session->getExecutor()->execute();


}
