#include <gtest/gtest.h>

#include <core/Tensor.h>

using namespace athena::core;

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

TEST(tensor_test, tensor_test_shape_constructor_Test) {
    unsigned int i[] = {3};
    TensorShape shape(i, 1);
    Tensor a(shape, DataType::FLOAT);

    ASSERT_EQ(a.getShape().dimensions(), 1);
    ASSERT_EQ(a.getShape().dim(0), 3);
}

TEST(tensor_test, tensor_test_data_load_Test) {
    unsigned int i[] = {3};
    TensorShape shape(i, 1);
    float af[] = {1, 2, 3};
    Tensor a(shape, DataType::FLOAT, reinterpret_cast<u_char *>(af));

    auto rf = reinterpret_cast<float *>(a.raw());

    for (int j = 0; j < 3; j++) {
        EXPECT_FLOAT_EQ(af[j], rf[j]);
    }
}