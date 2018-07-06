//
// Created by Александр Баташев on 06.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include <cmath>

namespace athena::backend::generic {

    athena::core::Tensor* msef ( athena::core::Tensor* x, athena::core::Tensor* y ) {

        auto xData = reinterpret_cast<float*>(x->raw());
        auto yData = reinterpret_cast<float*>(y->raw());

        auto resData = new float[x->getShape().total_size()];

#pragma omp parallel for
        for ( int i = 0; i < x->getShape().total_size(); i++ ) {
            resData[ i ] = pow( xData[ i ] - yData[ i ], 2.0f );
        }

        return new athena::core::Tensor( x->getShape(), athena::core::DataType::FLOAT,
                                         reinterpret_cast<unsigned char*>(resData));

    }

    athena::core::Tensor* mse ( athena::core::Tensor* x, athena::core::Tensor* y ) {

        // todo types
        return msef(x, y);

    }


    athena::core::Tensor* mse_derivf ( athena::core::Tensor* x,
                                       athena::core::Tensor* y ) {
        auto xData = reinterpret_cast<float*>(x->raw());
        auto yData = reinterpret_cast<float*>(y->raw());

        auto resData = new float[x->getShape().total_size()];

#pragma omp parallel for
        for ( int i = 0; i < x->getShape().total_size(); i++ ) {
            resData[ i ] = 2 * (xData[ i ] - yData[ i ] );
        }

        return new athena::core::Tensor( x->getShape(), athena::core::DataType::FLOAT,
                                         reinterpret_cast<unsigned char*>(resData));
    }

    athena::core::Tensor* mse_deriv ( athena::core::Tensor* x, athena::core::Tensor* y ) {
        return mse_derivf( x, y );
    }

}