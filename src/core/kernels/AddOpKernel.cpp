//
// Created by Александр Баташев on 25.05.2018.
//

#include <algorithm>
#include "AddOpKernel.h"

int athena::core::kernels::AddOpKernel::getOperandsCount() {
    return 2;
}

int *athena::core::kernels::AddOpKernel::getOutputShape(int *shape, int dim) {
    auto newShape = new int[dim];
    std::copy(shape, shape + dim, newShape);
    return newShape;
}
