#include "Tensor.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace athena::core {

    unsigned char* Tensor::get ( const size_t* idx ) const {
        return this->get( idx, shape->dimensions());
    }

    unsigned char* Tensor::get ( const size_t* idx, size_t length ) const {
        size_t helperDim = shape->total_size(), innerIdx = 0;

        for (
                size_t i = 0; i < length; i++
                ) {
            helperDim /= shape->dim( i );
            innerIdx += idx[ i ] * typesize( dataType ) * helperDim;
        }
        return this->data + innerIdx;
    }

    Tensor Tensor::getSubtensor ( const size_t* idx, size_t length ) const {
        TensorShape* tensorShape = new TensorShape(
                std::vector< size_t >(
                        shape->getShape().begin() + length, shape->getShape().end()));
        Tensor tensor( *tensorShape, dataType, get( idx, length ));
        return tensor;
    }

    Tensor Tensor::getSubtensor ( size_t id ) const {
        Tensor tmp = this->getSubtensor( &id, 1 );
        return tmp;
    }

    void Tensor::set ( const size_t* idx, void* item ) {
        size_t helperDim = shape->total_size(), innerIdx = 0;

        for (
                size_t i = 0; i < shape->dimensions(); i++
                ) {
            helperDim /= shape->dim( i );
            innerIdx += idx[ i ] * typesize( dataType ) * helperDim;
        }
        memcpy( data + innerIdx, item, typesize( dataType ));
    }

    void Tensor::set ( const size_t* idx, float item ) {
        if ( dataType != DataType::FLOAT ) {
            throw std::runtime_error( "Wrong type for tensor item" );
        }

        size_t helperDim = shape->total_size(), innerIdx = 0;

        for (
                size_t i = 0; i < shape->dimensions(); i++
                ) {
            helperDim /= shape->dim( i );
            innerIdx += idx[ i ] * typesize( dataType ) * helperDim;
        }
        memcpy( data + innerIdx, &item, sizeof( float ));
    }

    void Tensor::set ( const size_t* idx, double item ) {
        if ( dataType != DataType::DOUBLE ) {
            throw std::runtime_error( "Wrong type for tensor item" );
        }

        size_t helperDim = shape->total_size(), innerIdx = 0;

        for (
                size_t i = 0; i < shape->dimensions(); i++
                ) {
            helperDim /= shape->dim( i );
            innerIdx += idx[ i ] * typesize( dataType ) * helperDim;
        }
        memcpy( data + innerIdx, &item, sizeof( double ));
    }

    void Tensor::set ( const size_t* idx, int item ) {
        if ( dataType != DataType::INT ) {
            throw std::runtime_error( "Wrong type for tensor item" );
        }

        size_t helperDim = shape->total_size(), innerIdx = 0;

        for (
                size_t i = 0; i < shape->dimensions(); i++
                ) {
            helperDim /= shape->dim( i );
            innerIdx += idx[ i ] * typesize( dataType ) * helperDim;
        }
        memcpy( data + innerIdx, &item, sizeof( int ));
    }

    const TensorShape &Tensor::getShape () const {
        return *shape;
    }

    unsigned char* Tensor::raw () const {
        return data;
    }

    DataType Tensor::getType () const {
        return dataType;
    }

    size_t Tensor::getSizeType () const {
        if ( this->dataType == DataType::DOUBLE ) {
            return sizeof( double );
        } else if ( this->dataType == DataType::FLOAT ) {
            return sizeof( float );
        } else if ( this->dataType == DataType::INT ) {
            return sizeof( int );
        } else {
            throw std::runtime_error( "Wrong type for tensor item" );
        }
    }

    Tensor &Tensor::operator*= ( void* item ) {
        if ( this->getType() == DataType::INT ) {
            return this->operator*=( *(( int* ) item ));
        } else if ( this->getType() == DataType::FLOAT ) {
            return this->operator*=( *(( float* ) item ));
        } else if ( this->getType() == DataType::DOUBLE ) {
            return this->operator*=( *(( double* ) item ));
        } else {
            throw std::runtime_error( "Wrong type for tensor item" );
        }
    }

    Tensor &Tensor::operator*= ( float item ) {
        if ( this->getType() != DataType::FLOAT ) {
            throw std::runtime_error( "Type error with multiply tensor and float" );
        }

        auto* el = ( float* ) this->data;
        for (
                size_t i = 0, size = this->getShape().total_size();
                i < size;
                i++
                ) { //Can be vectorized
            el[ i ] *= item;
        }

        return *this;
    }

    Tensor &Tensor::operator*= ( double item ) {
        if ( this->getType() != DataType::DOUBLE ) {
            throw std::runtime_error( "Type error with multiply tensor and double" );
        }

        auto* el = ( double* ) this->data;
        for (
                size_t i = 0, size = this->getShape().total_size();
                i < size;
                i++
                ) { //Can be vectorized
            el[ i ] *= item;
        }

        return *this;
    }

    Tensor &Tensor::operator*= ( int item ) {
        if ( this->getType() != DataType::INT ) {
            throw std::runtime_error( "Type error with multiply tensor and int" );
        }

        auto* el = ( int* ) this->data;
        for (
                size_t i = 0, size = this->getShape().total_size();
                i < size;
                i++
                ) { //Can be vectorized
            el[ i ] *= item;
        }


        return *this;
    }
}
