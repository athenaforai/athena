//
// Created by Александр Баташев on 28.05.2018.
//

#ifndef ATHENA_ABSTRACTOPTIMIZER_H
#define ATHENA_ABSTRACTOPTIMIZER_H


#include "Node.h"

namespace athena::core {
    class AbstractOptimizer {
    protected:
        Node* logits;
    public:
        explicit AbstractOptimizer(Node* logits) : logits(logits){};
        ~AbstractOptimizer() = default;

        virtual void minimize() = 0;
    };
}


#endif //ATHENA_ABSTRACTOPTIMIZER_H
