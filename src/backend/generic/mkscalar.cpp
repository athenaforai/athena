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
        auto scalar = reinterpret_cast<float*>(&s);
        auto f = memoryManager->getPhysicalAddress( res->getStartAddress());
        memcpy( f, scalar, sizeof( float ));
    }
}