#ifndef ATHENA_ADDOPKERNEL_H
#define ATHENA_ADDOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {
    class AddOpKernel : public OpKernel {
    public:
        AddOpKernel () : OpKernel( OpCode::ADD, "add" ) {};

        int getOperandsCount () override;

        athena::core::TensorShape getOutputShape (
                athena::core::TensorShape* shapes,
                unsigned long size) override;

        std::vector< vm_word >
        getOpBytecode ( std::vector< vm_word > args, vm_word resultCell ) override;

        std::vector< vm_word > getDerivativeBytecode (
                int d, std::vector< vm_word > args,
                vm_word resultCell
        ) override;
    };
}


#endif //ATHENA_ADDOPKERNEL_H
