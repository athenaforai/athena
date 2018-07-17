#ifndef ATHENA_TENSMULNUMOPKERNEL_H
#define ATHENA_TENSMULNUMOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {
    class ScaleOpKernel : public athena::core::OpKernel {
    public:
        ScaleOpKernel () : OpKernel( OpCode::SCALE, "scale" ) {}

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

#endif
