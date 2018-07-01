//
// Created by Александр Баташев on 26.05.2018.
//
#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"

namespace athena::backend::generic {

    athena::core::Tensor* addf ( athena::core::Tensor* a, athena::core::Tensor* b ) {
        // todo find optimizations
        auto af = reinterpret_cast<float*>(a->raw ());
        auto bf = reinterpret_cast<float*>(b->raw ());
        auto cf = new float[b->getShape ().dim ( 0 )];

        for (
                int i = 0; i < b->getShape ().dim ( 0 ); i++
                ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
        return new athena::core::Tensor (
                const_cast<core::TensorShape &>(b->getShape ()),
                athena::core::DataType::FLOAT,
                reinterpret_cast<unsigned char*>(cf));
    }

    athena::core::Tensor* addd ( athena::core::Tensor* a, athena::core::Tensor* b ) {
        auto af = reinterpret_cast<double*>(a->raw ());
        auto bf = reinterpret_cast<double*>(b->raw ());
        auto cf = new double[b->getShape ().dim ( 0 )];

        for (
                int i = 0; i < b->getShape ().dim ( 0 ); i++
                ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
        return new athena::core::Tensor (
                const_cast<core::TensorShape &>(b->getShape ()),
                athena::core::DataType::DOUBLE,
                reinterpret_cast<unsigned char*>(cf));
    }

    athena::core::Tensor* addi ( athena::core::Tensor* a, athena::core::Tensor* b ) {
        auto af = reinterpret_cast<int*>(a->raw ());
        auto bf = reinterpret_cast<int*>(b->raw ());
        auto cf = new int[b->getShape ().dim ( 0 )];

        for (
                int i = 0; i < b->getShape ().dim ( 0 ); i++
                ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
        return new athena::core::Tensor (
                const_cast<core::TensorShape &>(b->getShape ()),
                athena::core::DataType::INT,
                reinterpret_cast<unsigned char*>(cf));
    }

    athena::core::Tensor* add ( athena::core::Tensor* a, athena::core::Tensor* b ) {

        if ( a->getShape () == b->getShape ()) {
            switch ( a->getType ()) {
                case athena::core::DataType::FLOAT:
                    return addf ( a, b );
                case athena::core::DataType::DOUBLE:
                    return addd ( a, b );
                case athena::core::DataType::INT:
                    return addi ( a, b );
            }
        }
        return nullptr;
    }
}