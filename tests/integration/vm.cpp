//
// Created by Александр Баташев on 27.05.2018.
//

#include <gtest/gtest.h>
#include <core/Session.h>
#include <core/Tensor.h>
#include <core/InputNode.h>
#include <ops/ops.h>

using namespace athena::core;

TEST(vm_test, vm_test_simple_Test) {
    Session sess;

    unsigned int shapeArr[] = {3};
    TensorShape shape(shapeArr, 1);

    float af[] = {1, 2, 3};
    float bf[] = {2, 3, 4};

    Tensor *a = new Tensor(shape, DataType::FLOAT, reinterpret_cast<u_char *>(af));
    Tensor *b = new Tensor(shape, DataType::FLOAT, reinterpret_cast<u_char *>(bf));

    auto an = InputNode(a);
    auto bn = InputNode(b);

    auto logits = athena::ops::add(&an, &bn);

    sess.prepare(logits);
    auto res = sess.run();
    res->raw();

    float resf[] = {3, 6, 7};
    auto resc = reinterpret_cast<float*>(res);

    for (int j = 0; j < 3; j++) {
         EXPECT_FLOAT_EQ(resc[j], resf[j]);
    }

}
