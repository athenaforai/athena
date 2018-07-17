//
// Created by Александр Баташев on 27.05.2018.
//

#ifndef ATHENA_MATMULOPKERNEL_H
#define ATHENA_MATMULOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {
    class MatMulOpKernel : public athena::core::OpKernel {
    public:
        MatMulOpKernel () : OpKernel( OpCode::MATMUL, "matmul" ) {};

        int getOperandsCount () override;

        athena::core::TensorShape &getOutputShape (
                const std::vector< athena::core::TensorShape & > &shapes ) override;

        athena::core::TensorShape &getDerivativeShape (
                int d,
                const std::vector< athena::core::TensorShape & > &shapes ) override;

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
