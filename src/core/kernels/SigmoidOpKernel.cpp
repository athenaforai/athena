//
// Created by Александр Баташев on 01.07.2018.
//

#include "SigmoidOpKernel.h"

athena::core::kernels::SigmoidOpKernel::SigmoidOpKernel ()
        : OpKernel ( OpCode::SIGMOID, "sigmoid" ) {}

int athena::core::kernels::SigmoidOpKernel::getOperandsCount () {
    return 1;
}

int* athena::core::kernels::SigmoidOpKernel::getOutputShape ( int* shape, int dim ) {
    auto* newShape = new int[dim];
    for (
            int i = 0; i < dim; i++
            ) {
        newShape[ i ] = shape[ i ];
    }
    return newShape;
}

std::vector< vm_word >
athena::core::kernels::SigmoidOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        unsigned long resultCell
) {

    std::vector< vm_word > bytecode;
    bytecode.push_back ( static_cast<vm_word>(OpCode::SIGMOID));
    bytecode.push_back ( args[ 0 ] );
    bytecode.push_back ( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::SigmoidOpKernel::getDerivativeBytecode (
        int d,
        std::vector< vm_word > args,
        vm_word resultCell
) {

    std::vector< vm_word > bytecode;
    bytecode.push_back ( static_cast<vm_word>(OpCode::SIGMOID_DERIV));
    bytecode.push_back ( args[ 0 ] );
    bytecode.push_back ( resultCell );

    return bytecode;
}
