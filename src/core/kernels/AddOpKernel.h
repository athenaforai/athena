#ifndef ATHENA_ADDOPKERNEL_H
#define ATHENA_ADDOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {
    class AddOpKernel : public OpKernel {
    public:
        AddOpKernel() : OpKernel(OpCode::ADD, "add") {};
        int getOperandsCount() override;
        int* getOutputShape(int* shape, int dim) override;

        std::vector<unsigned long> getOpBytecode(std::vector<unsigned long> args, unsigned long resultCell) override;

        std::vector<unsigned long> getDerivativeBytecode(int d, std::vector<unsigned long> args,
                                                       unsigned long resultCell) override;
    };
}


#endif //ATHENA_ADDOPKERNEL_H
