//
// Created by Александр Баташев on 06.07.2018.
//

#include "MSELoss.h"

athena::core::optimizers::MSELoss::MSELoss () :
        AbstractLossFunction( new MSEOpKernel()) {};

athena::core::optimizers::MSEOpKernel::MSEOpKernel () :
        OpKernel( OpCode::ADD, "mseloss" ) {}

int athena::core::optimizers::MSEOpKernel::getOperandsCount () {
    return 1;
}

athena::core::TensorShape
athena::core::optimizers::MSEOpKernel::getOutputShape ( athena::core::TensorShape* shapes,
                                                        unsigned long ) {
    return shapes[ 0 ];
}

std::vector< vm_word >
athena::core::optimizers::MSEOpKernel::getOpBytecode ( std::vector< vm_word > args,
                                                       unsigned long resultCell ) {

    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::MSE));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return std::vector< vm_word >();
}

std::vector< unsigned long >
athena::core::optimizers::MSEOpKernel::getDerivativeBytecode ( int d,
                                                               std::vector< unsigned long > args,
                                                               unsigned long resultCell ) {
    // todo depending on d the result needs to be scaled by -1
    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::MSE_DERIV));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return std::vector< vm_word >();
}
