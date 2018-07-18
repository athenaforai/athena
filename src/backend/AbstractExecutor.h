//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_ABSTRACTEXECUTOR_H
#define ATHENA_ABSTRACTEXECUTOR_H

#include <core/Tensor.h>
#include "AbstractMemoryManager.h"

namespace athena::backend {
    class AbstractExecutor {
    protected:
        std::vector< vm_word > bytecode;
    public:

        AbstractExecutor() = default;

        virtual void execute () = 0;

        virtual AbstractMemoryManager* getMemoryManager () = 0;

        void setBytecode (std::vector< vm_word >& bytecode);
    };
}


#endif //ATHENA_ABSTRACTEXECUTOR_H
