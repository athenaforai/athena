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

    void transpose ( GenericMemoryManager* memoryManager,
                     athena::core::Tensor* a,
                     athena::core::Tensor* res );

    void copy ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* res );

    void scale ( GenericMemoryManager* memoryManager,
                 athena::core::Tensor* c,
                 athena::core::Tensor* src,
                 athena::core::Tensor* res );

    void mse ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res );

    void mse_deriv ( GenericMemoryManager* memoryManager,
                     athena::core::Tensor* x,
                     athena::core::Tensor* y,
                     athena::core::Tensor* res );

    void mkscalar ( GenericMemoryManager* memoryManager,
                    unsigned long s,
                    athena::core::Tensor* res );
}
#endif //ATHENA_OPS_H
