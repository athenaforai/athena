//
// Created by Александр Баташев on 20.07.2018.
//
#pragma once
#ifndef ATHENA_DATAINITIALIZER_H
#define ATHENA_DATAINITIALIZER_H

#include <cstddef>
#include "AbstractInitializer.h"
#include <backend/AbstractMemoryManager.h>

namespace athena::core::initializers {
    class DataInitializer : public AbstractInitializer {
    private:
        void *data;
        size_t length;
    public:

        DataInitializer() : data( nullptr), length(0) {}

        DataInitializer ( const DataInitializer &src );

        DataInitializer &operator= ( const DataInitializer &src );

        ~DataInitializer ();

        void setData ( void* ptr, size_t length );

        void initialize ( athena::backend::AbstractMemoryManager* manager,
                          Tensor* tensor ) override;
    };
}


#endif //ATHENA_DATAINITIALIZER_H
