//
// Created by Александр Баташев on 05.07.2018.
//

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"

namespace athena::backend::generic {

    athena::core::Tensor* transposef ( athena::core::Tensor* a ) {
        auto data = reinterpret_cast<float*>(a->raw());
        auto transposedData = new float[a->getShape().total_size()];

        size_t m = a->getShape().dim( 1 );

#pragma omp parallel for
        for ( int n = 0; n < a->getShape().total_size(); n++ ) {
            int i = static_cast<int>(n / a->getShape().dim( 0 ));
            int j = static_cast<int>(n % a->getShape().dim( 0 ));

            transposedData[ n ] = data[ m * j + i ];
        }

        athena::core::TensorShape shape( { m, a->getShape().dim( 0 ) } );
        return new athena::core::Tensor( shape, athena::core::DataType::FLOAT,
                                         reinterpret_cast<unsigned char*>
                                         (transposedData));
    }


    /*
     * see https://stackoverflow.com/questions/16737298/what-is-the-fastest-way-to-transpose-a-matrix-in-c
     * for better solution
     */
    athena::core::Tensor* transpose ( athena::core::Tensor* a ) {

        if ( a != nullptr ) {
            if ( a->getType() == athena::core::DataType::FLOAT ) {
                return transposef( a );
            }
        }

        return nullptr;
    }

}