//
// Created by Александр Баташев on 28.05.2018.
//

#ifndef ATHENA_ABSTRACTOPTIMIZER_H
#define ATHENA_ABSTRACTOPTIMIZER_H


#include <core/InputNode.h>
#include <core/loss/AbstractLossFunction.h>
#include <core/Session.h>
#include "core/Node.h"

namespace athena::core::optimizers {
    class AbstractOptimizer {
    protected:
        std::vector< InputNode* > headNodes;
        std::vector< int > bytecode;

        unsigned long lastResultCell;
        Session* session;

        AbstractLossFunction* loss;
    public:
        explicit AbstractOptimizer ( AbstractLossFunction* loss ) : loss( loss ),
                                                                    lastResultCell( 0 ),
                                                                    session(
                                                                            nullptr
                                                                    ) {};

        ~AbstractOptimizer () = default;

        void init ( Session* session );

        virtual void prepare () = 0;

        virtual void minimize () = 0;
    };
}


#endif //ATHENA_ABSTRACTOPTIMIZER_H
