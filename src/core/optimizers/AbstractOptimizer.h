//
// Created by Александр Баташев on 28.05.2018.
//

#ifndef ATHENA_ABSTRACTOPTIMIZER_H
#define ATHENA_ABSTRACTOPTIMIZER_H


#include <core/InputNode.h>
#include "core/Node.h"

namespace athena::core::optimizers {
    class AbstractOptimizer {
    protected:
        std::vector<InputNode*> headNodes;
        std::vector<int> bytecode;

        Node* logits;
    public:
        explicit AbstractOptimizer(Node* logits) : logits(logits){};
        ~AbstractOptimizer() = default;

        virtual void prepare() = 0;
        virtual void minimize() = 0;
    };
}


#endif //ATHENA_ABSTRACTOPTIMIZER_H
