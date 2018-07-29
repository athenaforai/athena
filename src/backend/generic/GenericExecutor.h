//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_GENERICEXECUTOR_H
#define ATHENA_GENERICEXECUTOR_H

#include <backend/AbstractExecutor.h>
#include <stack>
#include <core/Tensor.h>
#include <utility>
#include <vector>
#include <core/opcodes.h>
#include "CPUDevice.h"

namespace athena::backend::generic {

    /**
     * <p>
     * GenericExecutor is the state of the art implementation of AbstractExecutor.
     * While we try to make it work fast, the main goal of this implementation
     * is to be mathematically correct and provide an example for more specific
     * implementation.
     * </p>
     * <p>
     * GenericExecutor executes
     * <a href="https://athenaframework.ml/athena/bytecode/basics.html">bytecode</a>
     * with standard CPU device. The actual implementations of bytecode commands
     * use BLAS to speed up calculations. There are several accelerators available:
     * <ul>
     * <li> <a href="https://developer.apple.com/documentation/accelerate">Apple
     * Accelerate Framework</a> </li>
     * <li> <a href="https://github.com/xianyi/OpenBLAS.git">OpenBLAS</a> </li>
     * <li> <a href="https://github.com/flame/blis.git">BLIS</a> </li>
     * </ul>
     * You can configure them during compile time. Other accelerators may be added
     * later.
     * </p>
     */
    class GenericExecutor : public athena::backend::AbstractExecutor {
    private:
//        athena::core::Tensor** memory;
//        int* intRegisters {};
//        std::stack< int > intStack;

//        std::vector< vm_word > &bytecode;

        CPUDevice* device;
    public:
        explicit GenericExecutor (
                CPUDevice* cpuDevice
        ) : AbstractExecutor(), device( cpuDevice ) {};

//        void execute () override;
//
//        AbstractMemoryManager* getMemoryManager() override ;

        void execute () override ;

        AbstractMemoryManager* getMemoryManager () override ;
    };
}


#endif //ATHENA_GENERICEXECUTOR_H
