#ifndef ATHENA_ADDOPKERNEL_H
#define ATHENA_ADDOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {
    class AddOpKernel : public OpKernel {
    public:
        AddOpKernel() : OpKernel(OpCode::ADD, "add") {};
        int getOperandsCount() override;
        int* getOutputShape(int* shape, int dim) override;

        std::vector<int> getOpBytecode(std::vector<int> args) override;
    };
}


#endif //ATHENA_ADDOPKERNEL_H
