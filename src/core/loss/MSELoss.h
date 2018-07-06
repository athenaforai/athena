//
// Created by Александр Баташев on 06.07.2018.
//

#ifndef ATHENA_MSELOSS_H
#define ATHENA_MSELOSS_H

#include <core/InputNode.h>
#include "AbstractLossFunction.h"

namespace athena::core::loss {

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
        explicit MSELoss ();

    };

}


#endif //ATHENA_MSELOSS_H
