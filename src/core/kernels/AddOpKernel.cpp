//
// Created by Александр Баташев on 25.05.2018.
//

#include <algorithm>
#include <vector>
#include "AddOpKernel.h"

int athena::core::kernels::AddOpKernel::getOperandsCount() {
    return 2;
}

int *athena::core::kernels::AddOpKernel::getOutputShape(int *shape, int dim) {
    auto newShape = new int[dim];
    std::copy(shape, shape + dim, newShape);
    return newShape;
}

std::vector<int> athena::core::kernels::AddOpKernel::getOpBytecode(std::vector<int> args) {
    std::vector<int> bytecode;

    bytecode.push_back(static_cast<int>(opCode));

    for (int arg : args) {
        bytecode.push_back(arg);
    }

    return bytecode;
}
