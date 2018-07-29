//
// Created by Александр Баташев on 05.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"

namespace athena::backend::generic {

    void copy ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* res ) {
        if ( x != nullptr ) {
            unsigned long total =
                    static_cast<unsigned int>(
                            athena::core::typesize( x->getType()) *
                            x->getShape().totalSize());

            auto newData = reinterpret_cast<unsigned char*>(
                    memoryManager->getPhysicalAddress( res->getStartAddress())
            );
            auto data = reinterpret_cast<unsigned char*>(
                    memoryManager->getPhysicalAddress( x->getStartAddress())
            );

#pragma omp parallel for
            for ( unsigned long i = 0; i < total; i++ ) {
                newData[ i ] = data[ i ];
            }

        }
    }

}