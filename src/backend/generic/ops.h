//
// Created by Александр Баташев on 27.05.2018.
//

#ifndef ATHENA_OPS_H
#define ATHENA_OPS_H

#include <core/Tensor.h>
#include <core/DataType.h>
#include "GenericMemoryManager.h"

namespace athena::backend::generic {
    void add ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* a,
               athena::core::Tensor* b,
               athena::core::Tensor* res
    );

    void matmul (
            GenericMemoryManager* memoryManager,
            bool aTransp,
            athena::core::Tensor* a,
            bool bTransp,
            athena::core::Tensor* b,
            athena::core::Tensor* res
    );

    void sigmoid ( GenericMemoryManager* memoryManager,
                   athena::core::Tensor* x,
                   athena::core::Tensor* res );

    void sigmoid_deriv ( GenericMemoryManager* memoryManager,
                         athena::core::Tensor* x,
                         athena::core::Tensor* res );

    athena::core::Tensor* transpose ( GenericMemoryManager* memoryManager,
                                      athena::core::Tensor* a );

    athena::core::Tensor* copy ( athena::core::Tensor* x );

    athena::core::Tensor* scale (
            athena::core::Tensor* c, athena::core::Tensor* src
    );

    athena::core::Tensor* mse ( athena::core::Tensor* x, athena::core::Tensor* y );

    athena::core::Tensor* mse_deriv ( athena::core::Tensor* x, athena::core::Tensor* y );

    athena::core::Tensor* mkscalar ( unsigned long s );
}
#endif //ATHENA_OPS_H
