//
// Created by Александр Баташев on 20.07.2018.
//

#ifndef ATHENA_VOIDINITIALIZER_H
#define ATHENA_VOIDINITIALIZER_H

#include "AbstractInitializer.h"

namespace athena::core::initializers {

    /**
     * VoidInitializer is the simplest initializer possible. It does not initialize
     * Tensor in any way. It is the default initializer for newly created Tensor
     */
    class VoidInitializer : public AbstractInitializer {
    public:
        void initialize ( athena::backend::AbstractMemoryManager*,
                          Tensor* ) override;
    };
}


#endif //ATHENA_VOIDINITIALIZER_H
