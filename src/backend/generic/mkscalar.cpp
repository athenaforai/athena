//
// Created by Александр Баташев on 06.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include <cstring>

namespace athena::backend::generic {

    void mkscalar ( GenericMemoryManager* memoryManager,
                    unsigned long s,
                    athena::core::Tensor* res ) {
//        auto f = new float[1];
        auto f = memoryManager->getPhysicalAddress( res->getStartAddress());
        memcpy( f, reinterpret_cast<float*>(&s), sizeof( float ));
    }
}