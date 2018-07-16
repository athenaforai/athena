//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_ABSTRACTEXECUTOR_H
#define ATHENA_ABSTRACTEXECUTOR_H

#include <core/Tensor.h>
#include "AbstractMemoryManager.h"

namespace athena::backend {
    class AbstractExecutor {
    public:
        virtual void execute () = 0;

        virtual AbstractMemoryManager* getMemoryManager() = 0;

//        virtual void setMemoryCell ( unsigned long id, athena::core::Tensor* tensor )
//        = 0;

//        virtual athena::core::Tensor* getMemoryCell ( unsigned long id ) = 0;
    };
}


#endif //ATHENA_ABSTRACTEXECUTOR_H
