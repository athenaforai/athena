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
        TensorShape* shape;
        unsigned char* data;
        DataType dataType;

    public:
        Tensor ( TensorShape &shape, DataType dataType ) :
                shape( new TensorShape( shape )), dataType( dataType ),
                data(
                        new unsigned char[this->shape->total_size() *
                                          typesize( dataType )]
                ) {};

        Tensor ( TensorShape &shape, DataType dataType, unsigned char* data ) :
                shape( new TensorShape( shape )),
                dataType( dataType ),
                data( data ) {};

        unsigned char* get ( const size_t* idx ) const;

        unsigned char* get ( const size_t* idx, size_t length ) const;

        Tensor getSubtensor ( const size_t* idx, size_t depth ) const;

        Tensor getSubtensor ( size_t id ) const;

        void set ( const size_t* idx, void* item );

        void set ( const size_t* idx, float item );

        void set ( const size_t* idx, double item );

        void set ( const size_t* idx, int item );

        const TensorShape &getShape () const;

        unsigned char* raw () const;

        DataType getType () const;

        size_t getSizeType () const;

        Tensor &operator*= ( void* item );

        Tensor &operator*= ( float item );

        Tensor &operator*= ( double item );

        Tensor &operator*= ( int item );
    };
}

#endif
