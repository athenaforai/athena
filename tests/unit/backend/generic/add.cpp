//
// Created by Александр Баташев on 27.05.2018.
//

#include <gtest/gtest.h>
#include <core/Tensor.h>
#include <backend/generic/ops.h>

using namespace athena::core;
using namespace athena::backend::generic;

TEST(add_op_test, add_1d)
{
//    size_t i[] = {3};
//    TensorShape shape(i, 1);
//    float af[] = {1, 2, 3};
//    Tensor a(shape, DataType::FLOAT, reinterpret_cast<u_char *>(af));
//
//    float bf[] = {4, 5, 6};
//    Tensor b(shape, DataType::FLOAT, reinterpret_cast<u_char *>(bf));
//
//    auto c = add(&a, &b);
//
//    float res[] = {5, 7, 9};
//    unsigned int idx[] = {0};
//    auto *cres = reinterpret_cast<unsigned char *>(res);
//    for (unsigned int j = 0; j < 3 * sizeof(float); j++) {
////        idx[0] = j;
//        EXPECT_EQ(cres[j], c->raw()[j]);
//    }
}
