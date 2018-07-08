//
// Created by Александр Баташев on 25.05.2018.
//

#include <algorithm>
#include <vector>
#include "AddOpKernel.h"

int athena::core::kernels::AddOpKernel::getOperandsCount () {
    return 2;
}

athena::core::TensorShape
athena::core::kernels::AddOpKernel::getOutputShape (
        athena::core::TensorShape* shapes,
        unsigned long size){
    return shapes[0];
}

std::vector< unsigned long > athena::core::kernels::AddOpKernel::getOpBytecode (
        std::vector< unsigned long > args,
        unsigned long resultCell ) {
    std::vector< unsigned long > bytecode;

    bytecode.push_back( static_cast<vm_word>(OpCode::ADD));

    bytecode.push_back(args[0]);
    bytecode.push_back(args[1]);

    bytecode.push_back(resultCell);

    return bytecode;
}

std::vector< unsigned long >
athena::core::kernels::AddOpKernel::getDerivativeBytecode (
        int d,
        std::vector< unsigned long > args,
        unsigned long resultCell ) {
    std::vector< unsigned long > bytecode;
    bytecode.push_back( static_cast<int>(OpCode::MKSCALAR));

    float unit = 1;
    auto u = reinterpret_cast<vm_word*>(&unit);

    bytecode.push_back( *u );
    bytecode.push_back( resultCell );

    return bytecode;

}
