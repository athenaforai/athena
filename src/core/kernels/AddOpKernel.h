#ifndef ATHENA_ADDOPKERNEL_H
#define ATHENA_ADDOPKERNEL_H

#include "../OpKernel.h"

namespace athena::core::kernels {
    class AddOpKernel : public OpKernel {
    public:
        AddOpKernel() : OpKernel(OpCode::ADD) {};
        int getOperandsCount() override;
        int* getOutputShape(int* shape, int dim) override;
    };
}


#endif //ATHENA_ADDOPKERNEL_H
