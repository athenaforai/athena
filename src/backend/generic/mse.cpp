//
// Created by Александр Баташев on 06.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include <cmath>

namespace athena::backend::generic {

    void msef ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res ) {

        auto xData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(x->getStartAddress()));
        auto yData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(y->getStartAddress()));
        auto resData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

#pragma omp parallel for
        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            resData[ i ] = pow( xData[ i ] - yData[ i ], 2.0f );
        }

    }

    void mse ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res ) {

        // todo types
        msef(memoryManager, x, y, res);

    }


    void mse_derivf ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* y,
                athena::core::Tensor* res ) {

        auto xData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(x->getStartAddress()));
        auto yData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(y->getStartAddress()));
        auto resData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

#pragma omp parallel for
        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            resData[ i ] = 2 * (xData[ i ] - yData[ i ] );
        }

    }

    void mse_deriv ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res ) {

        // todo types
        mse_derivf(memoryManager, x, y, res);

    }

}