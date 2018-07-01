//
// Created by Александр Баташев on 27.05.2018.
//

#ifndef ATHENA_MATMULOPKERNEL_H
#define ATHENA_MATMULOPKERNEL_H

#include <core/OpKernel.h>

namespace athena::core::kernels {
    class MatMulOpKernel : public athena::core::OpKernel {
    public:
        MatMulOpKernel () : OpKernel ( OpCode::MATMUL, "matmul" ) {};
    };
}


#endif //ATHENA_MATMULOPKERNEL_H
