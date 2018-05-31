#include "Tensor.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace athena::core {

    unsigned char *Tensor::get(const unsigned int *idx) const {
        return this->get(idx, shape->dimensions());
    }

    unsigned char *Tensor::get(const unsigned int *idx, unsigned int length) const {
        //auto *item = new unsigned char[typesize(dataType)];
        int helperDim = shape->total_size(), innerIdx = 0;

        for (unsigned int i = 0; i < length; i++) {
            helperDim /= shape->dim(i);
            innerIdx += idx[i] * typesize(dataType) * helperDim;
        }
        //memcpy(item, this->data + innerIdx, typesize(dataType));
        //return item;
        return this->data + innerIdx;
    }

    Tensor Tensor::getSubtensor(unsigned int *idx, unsigned int length) const {
        TensorShape *tensorShape = new TensorShape(std::vector<unsigned int>(shape->getShape().begin() + length, shape->getShape().end()));
        Tensor tensor(*tensorShape, dataType, get(idx, length));
        return tensor;
    }

    Tensor Tensor::getSubtensor(unsigned int id) const {
        Tensor tmp = this->getSubtensor(&id, 1);
        return tmp;
    }

    void Tensor::set(const unsigned int *idx, void *item) {
        int helperDim = shape->total_size(), innerIdx = 0;

        for (unsigned int i = 0; i < shape->dimensions(); i++) {
            helperDim /= shape->dim(i);
            innerIdx += idx[i] * typesize(dataType) * helperDim;
        }
        memcpy(data + innerIdx, item, typesize(dataType));
    }

    void Tensor::set(const unsigned int *idx, float item) {
        if (dataType != DataType::FLOAT) {
            throw std::runtime_error("Wrong type for tensor item");
        }

        int helperDim = shape->total_size(), innerIdx = 0;

        for (unsigned int i = 0; i < shape->dimensions(); i++) {
            helperDim /= shape->dim(i);
            innerIdx += idx[i] * typesize(dataType) * helperDim;
        }
        memcpy(data + innerIdx, &item, sizeof(float));
    }

    void Tensor::set(const unsigned int *idx, double item) {
        if (dataType != DataType::DOUBLE) {
            throw std::runtime_error("Wrong type for tensor item");
        }

        int helperDim = shape->total_size(), innerIdx = 0;

        for (unsigned int i = 0; i < shape->dimensions(); i++) {
            helperDim /= shape->dim(i);
            innerIdx += idx[i] * typesize(dataType) * helperDim;
        }
        memcpy(data + innerIdx, &item, sizeof(double));
    }

    void Tensor::set(const unsigned int *idx, int item) {
        if (dataType != DataType::INT) {
            throw std::runtime_error("Wrong type for tensor item");
        }

        int helperDim = shape->total_size(), innerIdx = 0;

        for (unsigned int i = 0; i < shape->dimensions(); i++) {
            helperDim /= shape->dim(i);
            innerIdx += idx[i] * typesize(dataType) * helperDim;
        }
        memcpy(data + innerIdx, &item, sizeof(int));
    }

    const TensorShape &Tensor::getShape() const{
        return *shape;
    }

    unsigned char *Tensor::raw() const{
        return data;
    }

    DataType Tensor::getType() const{
        return dataType;
    }

}
