//
// Created by Александр Баташев on 25.05.2018.
//
#pragma once
#ifndef ATHENA_TENSOR_H
#define ATHENA_TENSOR_H

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
        const TensorShape &shape;
//        unsigned char* data;
        DataType dataType;

        vm_word startAddress;

    public:

        Tensor ( const TensorShape &shape, DataType dataType ) :
                shape( shape ),
                dataType( dataType ),
                startAddress( 0 ) {};

        const TensorShape &getShape () const;

        DataType getType () const;

        vm_word getStartAddress ();

        void setStartAddress ( vm_word address );

        Tensor &operator[] ( unsigned int idx );
    };
}

#endif
