//
// Created by Александр Баташев on 26.05.2018.
//

#include <iostream>
#include "TensorShape.h"

unsigned int athena::core::TensorShape::total_size() {
    unsigned int ts = 1;
    for (unsigned int i : shape) {
        ts *= i;
    }
    return ts;
}

athena::core::TensorShape::TensorShape(unsigned int *shape, unsigned int length) {
    this->shape.insert(std::end(this->shape), shape, shape + length);
}

unsigned int athena::core::TensorShape::dimensions() const {
    return static_cast<unsigned int>(shape.size());
}

unsigned int athena::core::TensorShape::dim(unsigned int n) const {

    return n < shape.size() ? shape[n] : 0;
}

const std::vector<unsigned int>& athena::core::TensorShape::getShape() const {
    return shape;
}

bool athena::core::TensorShape::operator==(const athena::core::TensorShape &rhs) const {
    if (dimensions() != rhs.dimensions()) {
        return false;
    } else {
        for (unsigned int i = 0; i < dimensions(); i++) {
            if (dim(i) != rhs.dim(i)) {
                return false;
            }
        }
    }
    return true;
}

bool athena::core::TensorShape::operator!=(const athena::core::TensorShape &rhs) const {
    return !(*this == rhs);
}