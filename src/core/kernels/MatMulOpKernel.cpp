//
// Created by Александр Баташев on 27.05.2018.
//

#include "MatMulOpKernel.h"

int athena::core::kernels::MatMulOpKernel::getOperandsCount () {
    return 2;
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

athena::core::TensorShape &athena::core::kernels::MatMulOpKernel::getOutputShape (
        std::vector< athena::core::TensorShape > &shapes ) {
    TensorShape shape( { shapes[ 0 ].dim( 0 ), shapes[ 1 ].dim( 1 ) } );
    return shape;
}

athena::core::TensorShape &
athena::core::kernels::MatMulOpKernel::getDerivativeShape (
        int d,
        std::vector< athena::core::TensorShape > &shapes ) {
    if ( d == 0 ) {
        return shapes[ 0 ];
    } else {
        TensorShape s( { shapes[ 1 ].dim( 1 ), shapes[ 1 ].dim( 0 ) } );
        return s;
    }
}


