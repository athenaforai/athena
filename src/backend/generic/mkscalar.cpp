//
// Created by Александр Баташев on 06.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include <cstring>

namespace athena::backend::generic {

    athena::core::Tensor* mkscalar ( unsigned long s ) {
        auto f = new float[1];
        memcpy( f, reinterpret_cast<float*>(s), sizeof( float ));

        return new athena::core::Tensor( athena::core::TensorShape( { 1 } ),
                                         athena::core::DataType::FLOAT,
                                         reinterpret_cast<unsigned char*>(f));
    }
}