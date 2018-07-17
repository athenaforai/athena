//
// Created by Александр Баташев on 01.07.2018.
//

#include "SigmoidOpKernel.h"

athena::core::kernels::SigmoidOpKernel::SigmoidOpKernel ()
        : OpKernel( OpCode::SIGMOID, "sigmoid" ) {}

int athena::core::kernels::SigmoidOpKernel::getOperandsCount () {
    return 1;
}

std::vector< vm_word >
athena::core::kernels::SigmoidOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        unsigned long resultCell
) {

    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::SIGMOID));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::SigmoidOpKernel::getDerivativeBytecode (
        int d,
        std::vector< vm_word > args,
        vm_word resultCell
) {

    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::SIGMOID_DERIV));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

athena::core::TensorShape &
athena::core::kernels::SigmoidOpKernel::getDerivativeShape ( int d,
                                                             const std::vector< athena::core::TensorShape & > &shapes ) {
    return shapes[ 0 ];
}

athena::core::TensorShape &athena::core::kernels::SigmoidOpKernel::getOutputShape (
        const std::vector< athena::core::TensorShape & > &shapes ) {
    return shapes[ 0 ];
}
