//
// Created by Александр Баташев on 27.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"

namespace athena::backend::generic {

    void hadamardf ( GenericMemoryManager* memoryManager,
                    athena::core::Tensor* x,
                    athena::core::Tensor* y,
                    athena::core::Tensor* res ) {
        auto xData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(x->getStartAddress()));
        auto yData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(y->getStartAddress()));
        auto resData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

#pragma opm parallel for
        for ( unsigned long i = 0; i < x->getShape().totalSize(); i++ ) {
            resData[ i ] = xData[ i ] * yData[ i ];
        }
    }

    void hadamard ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* y,
                athena::core::Tensor* res ) {

        if ( x->getShape() != y->getShape()) {
            throw std::runtime_error( "Hadamard product is only defined for same-shaped"
                                      " Tensors" );
        }

        hadamardf( memoryManager, x, y, res );
    }
}