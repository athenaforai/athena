#include <gtest/gtest.h>
#include <core/kernels/AddOpKernel.h>

TEST(op_count_test, add_op_kernel_test) {
    auto addOp = new athena::core::kernels::AddOpKernel();
    athena::core::OpKernel* opPtr = addOp;

    ASSERT_EQ(opPtr->getOperandsCount(), 2);
}