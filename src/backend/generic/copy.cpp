//
// Created by Александр Баташев on 05.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"

namespace athena::backend::generic {

    athena::core::Tensor* copy ( athena::core::Tensor* x ) {
        if ( x != nullptr ) {
            unsigned long total =
                    static_cast<unsigned int>(athena::core::typesize( x->getType()) *
                                              x->getShape()
                                               .total_size());

            auto newData = new unsigned char[total];
            auto data = x->raw();

#pragma opm parallel for
            for ( unsigned long i = 0; i < total; i++ ) {
                newData[ i ] = data[ i ];
            }

            return new athena::core::Tensor(
                    const_cast<core::TensorShape &>(x->getShape()), x->getType(),
                    newData );

        }

        return nullptr;
    }

}