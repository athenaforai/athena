#include <gtest/gtest.h>
#include <core/kernels/AddOpKernel.h>
#include <core/TensorShape.h>

TEST(op_count_test, add_op_kernel_test) {
    auto addOp = new athena::core::kernels::AddOpKernel();
    athena::core::OpKernel* opPtr = addOp;

    ASSERT_EQ(opPtr->getOperandsCount(), 2);
}

TEST(op_shape_test, add_op_kernel_test) {
//    unsigned long ar[] = {1}, ar2[] = {1};
//    athena::core::TensorShape shapes[2];
//    shapes[0] = athena::core::TensorShape(ar, 1);
//    shapes[1] = athena::core::TensorShape(ar2, 1);
//    auto addOp = new athena::core::kernels::AddOpKernel();
//    athena::core::OpKernel* opPtr = addOp;
//
//    auto newShape = opPtr->getOutputShape(shapes, 0);
//
//
//    ASSERT_EQ(newShape.dimensions(), shapes[0].dimensions());
//    ASSERT_EQ(newShape.dim(0), shapes[0].dim(0));
//    ASSERT_EQ(newShape.dimensions(), shapes[1].dimensions());
//    ASSERT_EQ(newShape.dim(0), shapes[1].dim(0));
//    //ASSERT_EQ(newShape[1], shape[1]);
//    //ASSERT_EQ(newShape[2], shape[2]);

}