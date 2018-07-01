//
// Created by Александр Баташев on 01.07.2018.
//

#ifndef ATHENA_SIGMOIDOPKERNEL_H
#define ATHENA_SIGMOIDOPKERNEL_H


#include <core/OpKernel.h>

namespace athena::core::kernels {

    class SigmoidOpKernel : public OpKernel {
    public:
        SigmoidOpKernel ();

        int getOperandsCount () override;

        int* getOutputShape ( int* shape, int dim ) override;

        std::vector< vm_word >
        getOpBytecode ( std::vector< vm_word > args, vm_word resultCell ) override;

        std::vector< vm_word > getDerivativeBytecode (
                int d, std::vector< vm_word > args,
                vm_word resultCell
        ) override;

    };

}


#endif //ATHENA_SIGMOIDOPKERNEL_H
