//
// Created by Александр Баташев on 28.06.2018.
//

#ifndef ATHENA_GRADIENTDESCENT_H
#define ATHENA_GRADIENTDESCENT_H

#include <core/loss/AbstractLossFunction.h>
#include "AbstractOptimizer.h"

namespace athena::core::optimizers {
    class GradientDescent : public AbstractOptimizer {
    protected:
        float learningRate;
        std::tuple<std::vector<unsigned long>, unsigned long> getByteCode(
                AbstractLossFunction* node);
    public:
        GradientDescent(AbstractLossFunction* loss, float learningRate);

        void prepare() override;

    };
}


#endif //ATHENA_GRADIENTDESCENT_H
