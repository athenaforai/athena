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
#include "opcodes.h"

namespace athena::core {

    /**
     * <p>
     * In mathematics <strong>tensor</strong> is an abstract object, expressing some
     * definite type of multi-linear concept. See
     * <a href="https://en.wikipedia.org/wiki/Tensor_(intrinsic_definition)">Wikipedia</a>
     * for more info.
     * </p>
     * <p>
     * In Athena Tensor is an abstraction to represent data inside computational
     * graph. A 1-dimensional Tensor is either scalar or vector. A 2-dimensional
     * Tensor is a matrix.
     * </p>
     */
    class Tensor {
    private:
        TensorShape* shape;
//        unsigned char* data;
        DataType dataType;

        vm_word startAddress;

    public:
//        Tensor (const TensorShape &shape, DataType dataType ) :
//                shape( new TensorShape( shape )), dataType( dataType ),
//                data(
//                        new unsigned char[this->shape->total_size() *
//                                          typesize( dataType )]
//                ),
//                startAddress = {};

        Tensor ( const TensorShape &shape, DataType dataType ) :
                shape( new TensorShape( shape )),
                dataType( dataType ),
                startAddress( 0 ) {};

//        unsigned char* get ( const unsigned long* idx ) const;
//
//        unsigned char* get ( const unsigned long* idx, unsigned long length ) const;
//
//        Tensor getSubtensor ( const unsigned long* idx, unsigned long depth ) const;
//
//        Tensor getSubtensor ( unsigned long id ) const;
//
//        void set ( const unsigned long* idx, void* item );
//
//        void set ( const unsigned long* idx, float item );
//
//        void set ( const unsigned long* idx, double item );
//
//        void set ( const unsigned long* idx, int item );
//
        const TensorShape &getShape () const;

//
//        unsigned char* raw () const;
//
        DataType getType () const;

        vm_word getStartAddress();

        void setStartAddress ( vm_word address );

        Tensor &operator[](unsigned int idx);

//
//        unsigned long getSizeType () const;
//
//        Tensor &operator*= ( void* item );
//
//        Tensor &operator*= ( float item );
//
//        Tensor &operator*= ( double item );
//
//        Tensor &operator*= ( int item );
    };
}

#endif
