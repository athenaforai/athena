//
// Created by Александр Баташев on 26.05.2018.
//
//#include <core/Tensor.h>
//#include <core/DataType.h>
#include "ops.h"
#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#else
#include <cblas.h>
#endif

namespace athena::backend::generic {

    athena::core::Tensor* addf_1d(athena::core::Tensor* a, athena::core::Tensor* b) {
#ifdef __APPLE__
        auto y = new float[b->getShape().dim(0)];
        memcpy(y, b->raw(), b->getShape().dim(0));

        catlas_saxpby(a->getShape().dim(0), 1.0f, reinterpret_cast<float *>(a->raw()), 1, 1.0f, y, 1);
        return new athena::core::Tensor(a->getShape(), athena::core::DataType::FLOAT, reinterpret_cast<u_char *>(y));
#endif
        return nullptr;
    }

    athena::core::Tensor* add(athena::core::Tensor* a, athena::core::Tensor* b) {
//        if (a->getShape() != b->getShape()) {
//            throw std::runtime_error("Can't add two tensors with different dimensions");
//        }

        // assume equal sizes for now
        if (a->getShape().dimensions() == 1) {
            return addf_1d(a, b);
        }
        return nullptr;
    }
}