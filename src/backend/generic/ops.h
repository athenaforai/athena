//
// Created by Александр Баташев on 27.05.2018.
//

#ifndef ATHENA_OPS_H
#define ATHENA_OPS_H

#include <core/Tensor.h>
#include <core/DataType.h>

namespace athena::backend::generic {
    athena::core::Tensor* add ( athena::core::Tensor* a, athena::core::Tensor* b );

    athena::core::Tensor* matmul (
            bool aTransp, athena::core::Tensor* a, bool bTransp, athena::core::Tensor* b
    );

    athena::core::Tensor* sigmoid ( athena::core::Tensor* x );

    athena::core::Tensor* sigmoid_deriv ( athena::core::Tensor* x );
}
#endif //ATHENA_OPS_H
