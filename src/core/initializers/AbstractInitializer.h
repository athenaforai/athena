//
// Created by Александр Баташев on 20.07.2018.
//
#pragma once
#ifndef ATHENA_ABSTRACTINITIALIZER_H
#define ATHENA_ABSTRACTINITIALIZER_H

namespace athena::core {
    class Tensor;
}

namespace athena::backend {
    class AbstractMemoryManager;
}

namespace athena::core::initializers {

    /**
     * Initializers help developers load data into corresponding memory type.
     * Every Tensor is assigned with an Initializer &ndash; a subclass of
     * AbstractInitializer.
     * Data will be loaded into memory according to initializer's parameters.
     */
    class AbstractInitializer {
    public:
        /**
         * Loads data into memory.
         * This method <strong>must not</strong> be called by developers. It is
         * automatically called during initialization process.
         * @param manager Memory manager for the current device
         * @param tensor A pointer to a Tensor object, that current initializer is
         * assigned to
         */
        virtual void initialize ( athena::backend::AbstractMemoryManager* manager,
                                  Tensor* tensor ) = 0;
    };
}


#endif //ATHENA_ABSTRACTINITIALIZER_H
