#include "Tensor.h"

namespace athena::core {

    unsigned char *Tensor::get(unsigned int *idx) {
        auto *item = new unsigned char[typesize(dataType)];
        int innerIdx = 1;
        for (unsigned int i = 0; i < shape.dimensions() - 1; i++) {
            innerIdx *= idx[i] * typesize(dataType);
        }
        innerIdx += idx[shape.dimensions() - 1] * typesize(dataType);
        memcpy(item, this->data + innerIdx, typesize(dataType));
        return item;
    }

    void Tensor::set(unsigned int *idx, void *item) {
        int innerIdx = 1;
        for (unsigned int i = 0; i < shape.dimensions() - 1; i++) {
            innerIdx *= idx[i] * typesize(dataType);
        }
        innerIdx += idx[shape.dimensions() - 1] * typesize(dataType);
        memcpy(data + innerIdx, item, typesize(dataType));
    }

    void Tensor::set(unsigned int *idx, float item) {
        if (dataType != DataType::FLOAT) {
            throw std::runtime_error("Wrong type for tensor item");
        }

        int innerIdx = 1;
        for (unsigned int i = 0; i < shape.dimensions() - 1; i++) {
            innerIdx *= idx[i] * typesize(dataType);
        }
        innerIdx += idx[shape.dimensions() - 1] * typesize(dataType);
        memcpy(data + innerIdx, &item, sizeof(float));
    }

    void Tensor::set(unsigned int *idx, double item) {
        if (dataType != DataType::FLOAT) {
            throw std::runtime_error("Wrong type for tensor item");
        }

        int innerIdx = 1;
        for (unsigned int i = 0; i < shape.dimensions() - 1; i++) {
            innerIdx *= idx[i] * typesize(dataType);
        }
        innerIdx += idx[shape.dimensions() - 1] * typesize(dataType);
        memcpy(data + innerIdx, &item, sizeof(double));
    }

    void Tensor::set(unsigned int *idx, int item) {
        if (dataType != DataType::FLOAT) {
            throw std::runtime_error("Wrong type for tensor item");
        }

        int innerIdx = 1;
        for (unsigned int i = 0; i < shape.dimensions() - 1; i++) {
            innerIdx *= idx[i] * typesize(dataType);
        }
        innerIdx += idx[shape.dimensions() - 1] * typesize(dataType);
        memcpy(data + innerIdx, &item, sizeof(int));
    }

}
