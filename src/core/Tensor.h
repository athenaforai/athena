//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_TENSOR_H
#define ATHENA_TENSOR_H


#include <cstddef>
#include <utility>
#include <iostream>
#include "TensorShape.h"
#include "DataType.h"

namespace athena::core {

    class Tensor {
    private:
        TensorShape& shape;
        unsigned char *data;
        DataType dataType;

    public:
        Tensor(TensorShape &shape, DataType dataType) : shape(shape), dataType(dataType),
                                                        data(new unsigned char[this->shape.total_size() * typesize(dataType)]) {};

        Tensor(TensorShape &shape, DataType dataType, unsigned char *data) : shape(shape),
                                                                             dataType(dataType),
                                                                             data(data) {};

        unsigned char *get(const unsigned int *idx);

        unsigned char *get(const unsigned int *idx, unsigned int length);

        Tensor getSubtensor(unsigned int *idx, unsigned int depth);

        void set(const unsigned int *idx, void *item);

        void set(const unsigned int *idx, float item);

        void set(const unsigned int *idx, double item);

        void set(const unsigned int *idx, int item);

        const TensorShape& getShape();

        unsigned char* raw();

        DataType getType();
    };
}


#endif
