//
// Created by Александр Баташев on 01.07.2018.
//
#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include <cmath>

namespace athena::backend::generic {

    athena::core::Tensor* sigmoidd ( athena::core::Tensor* x ) {
        auto data = reinterpret_cast<double*>(x->raw());
        auto newData = new double[x->getShape().total_size()];

        for (
                int i = 0; i < x->getShape().total_size(); i++
                ) {
            newData[ i ] = 1.0 / ( 1 + exp( -data[ i ] ));
        }

        auto y = new athena::core::Tensor(
                const_cast<athena::core::TensorShape &>(x->getShape()),
                x->getType(),
                reinterpret_cast<unsigned char*>(newData));

        return y;

    }

    athena::core::Tensor* sigmoidf ( athena::core::Tensor* x ) {
        auto data = reinterpret_cast<float*>(x->raw());
        auto newData = new float[x->getShape().total_size()];

        for (
                int i = 0; i < x->getShape().total_size(); i++
                ) {
            newData[ i ] = 1.0f / ( 1 + exp( -data[ i ] ));
        }

        auto y = new athena::core::Tensor(
                const_cast<athena::core::TensorShape &>(x->getShape()),
                x->getType(),
                reinterpret_cast<unsigned char*>(newData));

        return y;
    }

    athena::core::Tensor* sigmoid ( athena::core::Tensor* x ) {
        if ( x->getType() == athena::core::DataType::FLOAT ) {
            return sigmoidf( x );
        } else if ( x->getType() == athena::core::DataType::DOUBLE ) {
            return sigmoidd( x );
        }

        return nullptr;
    }


    athena::core::Tensor* sigmoid_derivd ( athena::core::Tensor* x ) {
        auto data = reinterpret_cast<double*>(x->raw());
        auto newData = new double[x->getShape().total_size()];

        for (
                int i = 0; i < x->getShape().total_size(); i++
                ) {
            double s = 1.0f / ( 1 + exp( -data[ i ] ));
            newData[ i ] = s * ( 1 - s );
        }

        auto y = new athena::core::Tensor(
                const_cast<athena::core::TensorShape &>(x->getShape()),
                x->getType(),
                reinterpret_cast<unsigned char*>(newData));

        return y;

    }

    athena::core::Tensor* sigmoid_derivf ( athena::core::Tensor* x ) {
        auto data = reinterpret_cast<float*>(x->raw());
        auto newData = new float[x->getShape().total_size()];

        for (
                int i = 0; i < x->getShape().total_size(); i++
                ) {
            float s = 1.0f / ( 1 + exp( -data[ i ] ));
            newData[ i ] = s * ( 1 - s );
        }

        auto y = new athena::core::Tensor(
                const_cast<athena::core::TensorShape &>(x->getShape()),
                x->getType(),
                reinterpret_cast<unsigned char*>(newData));

        return y;
    }


    athena::core::Tensor* sigmoid_deriv ( athena::core::Tensor* x ) {
        if ( x->getType() == athena::core::DataType::FLOAT ) {
            return sigmoid_derivf( x );
        } else if ( x->getType() == athena::core::DataType::DOUBLE ) {
            return sigmoid_derivd( x );
        }

        return nullptr;
    }
}

