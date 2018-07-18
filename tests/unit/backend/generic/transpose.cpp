//
// Created by Александр Баташев on 05.07.2018.
//

#include <gtest/gtest.h>
#include <core/Tensor.h>
#include <backend/generic/ops.h>

using namespace athena::core;
using namespace athena::backend::generic;

TEST( transpose_op_test, transpose_2x2 ) {
//    TensorShape shape( { 2, 2 } );
//    float data[] = { 1, 2, 3, 4 };
//    float transposed[] = { 1, 3, 2, 4 };
//
//    Tensor a( shape, DataType::FLOAT, reinterpret_cast<unsigned char*>(data));
//    auto b = transpose( &a );
//
//    auto res = reinterpret_cast<float*>(b->raw());
//
//    for ( int i = 0; i < 4; i++ ) {
//        ASSERT_FLOAT_EQ( transposed[ i ], res[ i ] );
//    }

}
