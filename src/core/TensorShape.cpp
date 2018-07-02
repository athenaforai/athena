//
// Created by Александр Баташев on 26.05.2018.
//

#include <iostream>
#include "TensorShape.h"

size_t athena::core::TensorShape::total_size () const{
    size_t ts = 1;
    for (
        size_t i : shape
            ) {
        ts *= i;
    }
    return ts;
}

athena::core::TensorShape::TensorShape ( size_t* shape, size_t length ){
    this->shape.insert ( std::end ( this->shape ), shape, shape + length );
}

size_t athena::core::TensorShape::dimensions () const{
    return static_cast<size_t>(shape.size ());
}

size_t athena::core::TensorShape::dim ( size_t n ) const{
    return n < shape.size () ? shape[ n ] : 0;
}

const std::vector< size_t > &athena::core::TensorShape::getShape () const{
    return shape;
}

bool
athena::core::TensorShape::operator== ( const athena::core::TensorShape &rhs ) const{
    if ( dimensions () != rhs.dimensions ()) {
        return false;
    } else {
        for (
                size_t i = 0; i < dimensions (); i++
                ) {
            if ( dim ( i ) != rhs.dim ( i )) {
                return false;
            }
        }
    }
    return true;
}

bool
athena::core::TensorShape::operator!= ( const athena::core::TensorShape &rhs ) const{
    return !( *this == rhs );
}