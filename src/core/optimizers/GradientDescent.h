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

        std::tuple< std::vector< unsigned long >, unsigned long > getByteCode (
                athena::core::loss::AbstractLossFunction* node
        );

    public:
        GradientDescent ( athena::core::loss::AbstractLossFunction* loss,
                          float learningRate );

        /**
         * <p> Generate bytecode for backpropagation </p>
         * <p> The whole algorithm:
         * <ol>
         * <li> Calculate actual error E </li>
         * <li> Let's Q - queue of nodes, EQ - queue of errors
         * <ol>
         * <li> \f$ node \rightarrow Q \f$ </li>
         * <li> \f$ E \rightarrow EQ \f$ </li>
         * </ol>
         * </li>
         * <li> For each node N in Q
         * <ol>
         * <li> \f$ EQ \rightarrow E \f$ </li>
         * <li> If this is variable node, adjust weights: \f$ N = N - \alpha * E \f$ </li>
         * <li> If this is regular node, for each incoming node I:
         * <ol>
         * <li> If I is constant, skip </li>
         * <li> \f$ E_i = D_i \odot E \f$, where \f$ E_i \f$ is the new error value,
         * \f$ D_i \f$ - derivative of N with respect to I, \f$ \odot \f$ - Hadamard
         * (elementwise) product. </li>
         * <li> \f$ E_i \rightarrow EQ \f$ </li>
         * <li> \f$ I \rightarrow Q \f$ </li>
         * </ol>
         * </li>
         * </ol>
         * </li>
         * </ol>
         * </p>
         */
        void prepare () override;

        void minimize() override ;

    };
}


#endif //ATHENA_GRADIENTDESCENT_H
