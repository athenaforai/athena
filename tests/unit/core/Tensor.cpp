#include <gtest/gtest.h>

#include <core/Tensor.h>

using namespace athena::core;

TEST(tensor_test, tensor_test_set_get_int){
    size_t ar[] = {3, 3, 3}, ar2[] = {2, 1, 2}, ar3[] = {2, 1, 2};
    int a = 5;
    TensorShape shape(ar, 3);
    Tensor tensor(shape, DataType::INT);
    tensor.set(ar2, a);
    ASSERT_EQ(a, *((int*)tensor.get(ar3)));
}

TEST(tensor_test, tensor_test_set_get_float){
    size_t ar[] = {3, 3, 3}, ar2[] = {2, 1, 2}, ar3[] = {2, 1, 2};
    float a = 5;
    TensorShape shape(ar, 3);
    Tensor tensor(shape, DataType::FLOAT);
    tensor.set(ar2, a);
    ASSERT_EQ(a, *((float*)tensor.get(ar3)));
}

TEST(tensor_test, tensor_test_set_get_double){
    size_t ar[] = {3, 3, 3}, ar2[] = {2, 1, 2}, ar3[] = {2, 1, 2};
    double a = 5;
    TensorShape shape(ar, 3);
    Tensor tensor(shape, DataType::DOUBLE);
    tensor.set(ar2, a);
    ASSERT_EQ(a, *((double*)tensor.get(ar3)));
}

TEST(tensor_test, tensor_test_set_get_void_pointer){
    size_t ar2[] = {2, 1, 2}, ar3[] = {2, 1, 2};
    double a = 5;
    TensorShape shape({3, 3, 3});
    Tensor tensor(shape, DataType::DOUBLE);
    tensor.set(ar2, &a);
    ASSERT_EQ(a, *((double*)tensor.get(ar3)));
}

TEST(tensor_test, tensor_test_shape_constructor_Test) {
    size_t i[] = {3};
    TensorShape shape(i, 1);
    Tensor a(shape, DataType::FLOAT);

    ASSERT_EQ(a.getShape().dimensions(), 1);
    ASSERT_EQ(a.getShape().dim(0), 3);
}

TEST(tensor_test, tensor_test_data_load_Test) {
    size_t i[] = {3};
    TensorShape shape(i, 1);
    float af[] = {1, 2, 3};
    Tensor a(shape, DataType::FLOAT, reinterpret_cast<u_char *>(af));

    auto rf = reinterpret_cast<float *>(a.raw());

    for (int j = 0; j < 3; j++) {
        EXPECT_FLOAT_EQ(af[j], rf[j]);
    }
}

TEST(tensor_test, tensor_test_get_subtensor)
{
    size_t ar[] = {3, 3, 3}, ar2[] = {2, 1, 2}, ar3[] = {2, 1, 2}, ind[3], indSub[2], indexSubtensor = 1;
    int testArr[3][3][3], val = 0;
    TensorShape shape(ar, 3);
    Tensor tensor(shape, DataType::INT);

    std::cout << "Shape : " << std::endl;
    for (size_t i : tensor.getShape().getShape())
        std::cout << i << " ";
    std::cout << std::endl;

    for(size_t i = 0; i < 3; i++)
        for(size_t j = 0; j < 3; j++)
            for(size_t k = 0; k < 3; k++) {
                ind[0] = i;
                ind[1] = j;
                ind[2] = k;
                tensor.set(ind, val);
                std::cout << "IND : " << ind[0] << " " << ind[1] << " " << ind[2] << " GET : " << *((int*)tensor.get(ind)) << std::endl;
                testArr[i][j][k] = val;
                val++;
            }

    Tensor subtensor = tensor.getSubtensor(indexSubtensor);

    std::cout << "Shape : " << subtensor.getShape().dimensions() << std::endl;
    for (size_t i : subtensor.getShape().getShape())
        std::cout << i << " ";
    std::cout << std::endl;



        for(size_t j = 0; j < 3; j++)
            for(size_t k = 0; k < 3; k++) {
                ind[0] = indexSubtensor;
                ind[1] = j;
                ind[2] = k;
                indSub[0] = j;
                indSub[1] = k;
                std::cout << "IND : " << ind[0] << " " << ind[1] << " " << ind[2]
                          << " GET : " << ((int*)tensor.get(ind)) << "; GETSUB : " << ((int*)subtensor.get(indSub)) << std::endl;
                //ASSERT_EQ(testArr[indexSubtensor][j][k], *((int*)subtensor.get(ind)));
            }

}