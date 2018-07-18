//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_ABSTRACTEXECUTOR_H
#define ATHENA_ABSTRACTEXECUTOR_H

#include <core/Tensor.h>
#include "AbstractMemoryManager.h"

namespace athena::backend {

    /**
     * An Executor is a Virtual Machine that runs Athena
     * <a href="https://athenaframework.ml/athena/bytecode/basics.html">bytecode</a>.
     * AbstractExecutor is the base class for all executors.
     */
    class AbstractExecutor {
    protected:
        std::vector< vm_word > bytecode;
    public:

        AbstractExecutor() = default;

        /**
         * Executes current bytecode. After execution threads state must be
         * reset. However, memory state (Memory manager and its data) must
         * persist.
         */
        virtual void execute () = 0;

        /**
         *
         * @return Memory Manager for current device
         */
        virtual AbstractMemoryManager* getMemoryManager () = 0;

        /**
         * Sets new bytecode
         * @param bytecode Bytecode
         */
        void setBytecode (std::vector< vm_word >& bytecode);
    };
}


#endif //ATHENA_ABSTRACTEXECUTOR_H
