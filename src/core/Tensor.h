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
        TensorShape *shape;
        unsigned char *data;
        DataType dataType;

    public:
        Tensor(TensorShape &shape, DataType dataType) : shape(new TensorShape(shape)), dataType(dataType),
                                                        data(new unsigned char[this->shape->total_size() * typesize(dataType)]) {};

        Tensor(TensorShape &shape, DataType dataType, unsigned char *data) : shape(new TensorShape(shape)),
                                                                             dataType(dataType),
                                                                             data(data) {};

        unsigned char *get(const unsigned int *idx) const;

        unsigned char *get(const unsigned int *idx, unsigned int length) const;

        Tensor getSubtensor(unsigned int *idx, unsigned int depth) const;

        Tensor getSubtensor(unsigned int id) const;

        void set(const unsigned int *idx, void *item);

        void set(const unsigned int *idx, float item);

        void set(const unsigned int *idx, double item);

        void set(const unsigned int *idx, int item);

        const TensorShape& getShape() const;

        unsigned char* raw() const;

        DataType getType() const;
    };
}


#endif
