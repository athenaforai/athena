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
    class GenericExecutor : public athena::backend::AbstractExecutor {
    private:
//        athena::core::Tensor** memory;
//        int* intRegisters {};
//        std::stack< int > intStack;

        std::vector< vm_word > &bytecode;

        CPUDevice* device;
    public:
        explicit GenericExecutor (
                std::vector< vm_word > &bytecode, unsigned long maxMem,
                CPUDevice* cpuDevice
        ) : bytecode( bytecode ), device( cpuDevice ) {

        };

//        void execute () override;
//
//        AbstractMemoryManager* getMemoryManager() override ;

        void execute () override ;

        AbstractMemoryManager* getMemoryManager () override ;
    };
}


#endif //ATHENA_GENERICEXECUTOR_H
