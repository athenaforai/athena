//
// Created by Александр Баташев on 06.07.2018.
//

#ifndef ATHENA_MSELOSS_H
#define ATHENA_MSELOSS_H

#include "AbstractLossFunction.h"

namespace athena::core::optimizers {

    class MSEOpKernel : public OpKernel {
    public:
        MSEOpKernel ();

        int getOperandsCount () override ;

        athena::core::TensorShape getOutputShape (
                athena::core::TensorShape* shapes,
                unsigned long) override ;

        std::vector< unsigned long >
        getOpBytecode (
                std::vector< unsigned long > args,
                unsigned long resultCell
        ) override ;

        std::vector< unsigned long > getDerivativeBytecode (
                int d, std::vector< unsigned long > args,
                unsigned long resultCell
        ) override ;
    };

    class MSELoss : public AbstractLossFunction {
    public:
        MSELoss ();

    };

}


#endif //ATHENA_MSELOSS_H
