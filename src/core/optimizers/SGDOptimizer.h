//
// Created by Александр Баташев on 20.06.2018.
//

#ifndef ATHENA_SGDOPTIMIZER_H
#define ATHENA_SGDOPTIMIZER_H


#include "AbstractOptimizer.h"

namespace athena::core::optimizers {

    class SGDOptimizer : public AbstractOptimizer {

    public:
        explicit SGDOptimizer ( athena::core::loss::AbstractLossFunction* logits ) :
                AbstractOptimizer( logits ) {};

    };

    typedef SGDOptimizer SGD;
}

#endif //ATHENA_SGDOPTIMIZER_H
