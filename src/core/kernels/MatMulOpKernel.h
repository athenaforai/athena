//
// Created by Александр Баташев on 27.05.2018.
//

#ifndef ATHENA_MATMULOPKERNEL_H
#define ATHENA_MATMULOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {

    /**
     * Performs matrix multiplication of given Tensors.
     * Matrix is a 2-D Tensor. The main restriction for this operation is
     * that the number of columns for the first column must be equal to the number
     * of rows for the second matrix. The reason to introduce this operation apart
     * from Tensor product is that it is widely adopted by different acceleration
     * mechanism (BLAS, cuBLAS, Accelerate Framework, etc)
     */
    class MatMulOpKernel : public athena::core::OpKernel {
    public:
        MatMulOpKernel () : OpKernel( OpCode::MATMUL, "matmul" ) {};

        int getOperandsCount () override;

        athena::core::TensorShape &getOutputShape (
                std::vector< athena::core::TensorShape > &shapes ) override;

        athena::core::TensorShape &getDerivativeShape (
                int d,
                std::vector< athena::core::TensorShape > &shapes ) override;

        std::vector< vm_word >
        getOpBytecode ( std::vector< vm_word > args, vm_word resultCell ) override;

        std::vector< vm_word > getDerivativeBytecode (
                int d,
                std::vector< vm_word > args,
                vm_word resultCell
        ) override;
    };
}


#endif //ATHENA_MATMULOPKERNEL_H
