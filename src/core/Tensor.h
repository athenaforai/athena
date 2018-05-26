//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_TENSOR_H
#define ATHENA_TENSOR_H


#include <cstddef>
#include <utility>
#include "TensorShape.h"
#include "DataType.h"

namespace athena::core {

    class Tensor {
    private:
        TensorShape shape;
        unsigned char *data;
        DataType dataType;

    public:
        explicit Tensor(TensorShape shape, DataType dataType) : shape(std::move(shape)), dataType(dataType),
                                                                data(new unsigned char[shape.total_size()]) {};

        unsigned char *get(unsigned int *idx);

        void set(unsigned int *idx, void *item);

        void set(unsigned int *idx, float item);

        void set(unsigned int *idx, double item);

        void set(unsigned int *idx, int item);
    };
}


#endif
