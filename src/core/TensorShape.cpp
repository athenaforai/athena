//
// Created by Александр Баташев on 26.05.2018.
//

#include <iostream>
#include "TensorShape.h"

unsigned long athena::core::TensorShape::totalSize () const {
    unsigned long ts = 1;
    for (
        unsigned long i : shape
            ) {
        ts *= i;
    }
    return ts;
}

athena::core::TensorShape::TensorShape ( unsigned long* shape, unsigned long length ) {
    this->shape.insert( std::end( this->shape ), shape, shape + length );
}

unsigned long athena::core::TensorShape::dimensions () const {
    return shape.size();
}

unsigned long athena::core::TensorShape::dim ( unsigned long n ) const {
    return n < shape.size() ? shape[ n ] : 0;
}

const std::vector< unsigned long > &athena::core::TensorShape::getShape () const {
    return shape;
}

bool
athena::core::TensorShape::operator== ( const athena::core::TensorShape &rhs ) const {
    if ( dimensions() != rhs.dimensions()) {
        return false;
    } else {
        for (
                unsigned long i = 0; i < dimensions(); i++
                ) {
            if ( dim( i ) != rhs.dim( i )) {
                return false;
            }
        }
    }
    return true;
}

bool
athena::core::TensorShape::operator!= ( const athena::core::TensorShape &rhs ) const {
    return !( *this == rhs );
}

athena::core::TensorShape::TensorShape ( const athena::core::TensorShape & src) {
    this->shape = src.shape;

}

athena::core::TensorShape &
athena::core::TensorShape::operator= ( const athena::core::TensorShape &src ) {
    if ( this != &src ) {
        this->shape = src.shape;
    }
    return *this;
}
