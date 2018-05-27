//
// Created by Александр Баташев on 26.05.2018.
//
#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#if defined(__APPLE__) && !defined(FORCE_OPENBLAS)
#include <Accelerate/Accelerate.h>
#else
#include "cblas.h"
#endif

namespace athena::backend::generic {

    athena::core::Tensor* addf_1d(athena::core::Tensor* a, athena::core::Tensor* b) {
#if defined(__APPLE__) && !defined(FORCE_OPENBLAS)
        auto y = new float[b->getShape().dim(0)];
        memcpy(y, b->raw(), b->getShape().dim(0) * athena::core::typesize(b->getType()));

        catlas_saxpby(a->getShape().dim(0), 1.0f, reinterpret_cast<float *>(a->raw()), 1, 1.0f, y, 1);
        return new athena::core::Tensor(b->getShape(),
                                        athena::core::DataType::FLOAT,
                                        reinterpret_cast<unsigned char *>(y));
#else
        auto af = reinterpret_cast<float *>(a->raw());
        auto bf = reinterpret_cast<float *>(b->raw());
        auto cf = new float[b->getShape().dim(0)];

        for (int i = 0; i < b->getShape().dim(0); i++) {
            cf[i] = af[i] + bf[i];
        }
        return new athena::core::Tensor(b->getShape(),
                                        athena::core::DataType::FLOAT,
                                        reinterpret_cast<unsigned char *>(cf));
#endif
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