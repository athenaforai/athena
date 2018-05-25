#ifndef ATHENA_ADDOPKERNEL_H
#define ATHENA_ADDOPKERNEL_H

#include "../OpKernel.h"

namespace athena::core::kernels {
    class AddOpKernel : OpKernel {
    public:
        AddOpKernel() : OpKernel(), opCode(OpCode::ADD) {};
    };
}


#endif //ATHENA_ADDOPKERNEL_H
