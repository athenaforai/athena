#include <gtest/gtest.h>
#include <core/kernels/AddOpKernel.h>

TEST(op_count_test, add_op_kernel_test) {
    auto addOp = new athena::core::kernels::AddOpKernel();
    athena::core::OpKernel* opPtr = addOp;

    ASSERT_EQ(opPtr->getOperandsCount(), 2);
}

TEST(op_shape_test, add_op_kernel_test) {
    auto addOp = new athena::core::kernels::AddOpKernel();
    athena::core::OpKernel* opPtr = addOp;

    int shape[] = {1, 2, 3};
    auto newShape = opPtr->getOutputShape(shape, 3);

    ASSERT_NE(newShape, shape);
    ASSERT_EQ(newShape[0], shape[0]);
    ASSERT_EQ(newShape[1], shape[1]);
    ASSERT_EQ(newShape[2], shape[2]);

}