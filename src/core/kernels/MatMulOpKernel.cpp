//
// Created by Александр Баташев on 27.05.2018.
//

#include "MatMulOpKernel.h"

int athena::core::kernels::MatMulOpKernel::getOperandsCount () {
    return 2;
}

athena::core::TensorShape
athena::core::kernels::MatMulOpKernel::getOutputShape (
        athena::core::TensorShape* shapes,
        unsigned long size) {
    return TensorShape( nullptr, 0); // todo
}

std::vector< vm_word >
athena::core::kernels::MatMulOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        vm_word resultCell ) {

    std::vector< vm_word > bytecode;

    bytecode.push_back( static_cast<vm_word>(OpCode::MATMUL));
    bytecode.push_back( 0 );
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( 0 );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::MatMulOpKernel::getDerivativeBytecode ( int d,
                                                               std::vector< vm_word > args,
                                                               vm_word resultCell ) {

    std::vector< vm_word > bytecode;

    if ( d == 0 ) {
        bytecode.push_back( static_cast<vm_word>(OpCode::COPY));
        bytecode.push_back( args[ 0 ] );
    } else {
        bytecode.push_back( static_cast<vm_word>(OpCode::TRANSPOSE));
        bytecode.push_back( args[ 1 ] );
    }
    bytecode.push_back( resultCell );

    return std::vector< vm_word >();
}


