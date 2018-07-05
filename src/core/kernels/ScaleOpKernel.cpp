#include "ScaleOpKernel.h"

int athena::core::kernels::ScaleOpKernel::getOperandsCount () {
    return 2;
}

athena::core::TensorShape
athena::core::kernels::ScaleOpKernel::getOutputShape (
        athena::core::TensorShape* shapes,
        unsigned long size ) {
    return shapes[1];
}

std::vector< vm_word >
athena::core::kernels::ScaleOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        vm_word resultCell ) {
    std::vector< vm_word > bytecode;

    bytecode.push_back( static_cast<vm_word>(OpCode::SCALE));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::ScaleOpKernel::getDerivativeBytecode ( int d,
                                                               std::vector< vm_word > args,
                                                               vm_word resultCell ) {
    std::vector< vm_word > bytecode;

    //?? CodeOp and Args todo

    bytecode.push_back( resultCell );

    return std::vector< vm_word >();
}
