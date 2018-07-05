//
// Created by Александр Баташев on 25.05.2018.
//

#include <algorithm>
#include <vector>
#include "AddOpKernel.h"

int athena::core::kernels::AddOpKernel::getOperandsCount () {
    return 2;
}

int* athena::core::kernels::AddOpKernel::getOutputShape ( int* shape, int dim ) {
    auto newShape = new int[dim];
    std::copy( shape, shape + dim, newShape );
    return newShape;
}

std::vector< unsigned long > athena::core::kernels::AddOpKernel::getOpBytecode (
        std::vector< unsigned long > args, unsigned long resultCell
) {
    std::vector< unsigned long > bytecode;

    bytecode.push_back( static_cast<unsigned long>(opCode));

    for (
        unsigned long &arg : args
            ) {
        bytecode.push_back( arg );
    }

    bytecode.push_back( static_cast<int>(resultCell));

    return bytecode;
}

std::vector< unsigned long >
athena::core::kernels::AddOpKernel::getDerivativeBytecode (
        int d, std::vector< unsigned long > args,
        unsigned long resultCell
) {
    std::vector< unsigned long > bytecode;
    bytecode.push_back( static_cast<int>(OpCode::MKSCALAR));

    bytecode.push_back( resultCell );
    bytecode.push_back( 1 );

    return bytecode;

}
