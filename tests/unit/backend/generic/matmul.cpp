//
// Created by Александр Баташев on 02.07.2018.
//

#include <gtest/gtest.h>
#include <core/Tensor.h>
#include <backend/generic/ops.h>

using namespace athena::core;
using namespace athena::backend::generic;

TEST( matmul_op_test, matmul_unit ){
    TensorShape shape ( { 3, 3 } );

    float data1[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    float data2[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

    Tensor a ( shape, DataType::FLOAT, reinterpret_cast<unsigned char*>( data1 ));
    Tensor b ( shape, DataType::FLOAT, reinterpret_cast<unsigned char*>( data2 ));

    auto res = matmul ( false, &a, false, &b );

    auto resData = reinterpret_cast<float*>(res->raw ());

    for ( int i = 0; i < 9; i++ ) {
        ASSERT_FLOAT_EQ ( data1[ i ], resData[ i ] );
    }


}

