//
// Created by Александр Баташев on 26.05.2018.
//
#include <core/Tensor.h>
#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#else
#include <cblas.h>
#endif

namespace athena::backend::generic {
    void add(athena::core::Tensor* a, athena::core::Tensor* b) {
        if (a->getShape() != b->getShape()) {
            throw std::runtime_error("Can't add two tensors with different dimensions");
        }
    }
}