//
// Created by Александр Баташев on 27.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include "GenericMemoryManager.h"

namespace athena::backend::generic {

    void mul ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* a,
               athena::core::Tensor* b,
               athena::core::Tensor* res ) {

        if ( a->getShape().dimensions() == 1 ) {
            scale( memoryManager, a, b, res );
        } else if ( b->getShape().dimensions() == 1 ) {
            scale( memoryManager, b, a, res );
        } else if ( a->getShape().dimensions() == 2 && b->getShape().dimensions() == 2 ) {
            matmul( memoryManager, false, a, false, b, res );
        } else {
            throw std::runtime_error( "Tensor product is not implemented yet" );
        }

    }

}