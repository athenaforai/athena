#include "Tensor.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace athena::core {

    const TensorShape &Tensor::getShape () const {
        return shape;
    }

    DataType Tensor::getType () const {
        return dataType;
    }

    vm_word Tensor::getStartAddress () {
        return startAddress;
    }

    Tensor &Tensor::operator[] ( unsigned int idx ) {
        std::vector<unsigned long> dims;

        for ( int i = 1; i < shape.dimensions(); i++ ) {
            dims.push_back( shape.dim( static_cast<unsigned long>(i)));
        }

        Tensor* res = new Tensor( TensorShape( dims ), dataType );
        res->startAddress =
                startAddress + idx * res->shape.totalSize() * typesize( dataType );

        return *res;
    }

    void Tensor::setStartAddress ( vm_word address ) {
        startAddress = address;
    }

}
