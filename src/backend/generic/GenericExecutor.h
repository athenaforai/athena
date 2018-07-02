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

namespace athena::backend::generic {
    class GenericExecutor : public athena::backend::AbstractExecutor {
    private:
        athena::core::Tensor** memory;
        int* intRegisters {};
        std::stack< int > intStack;

        std::vector< vm_word > &bytecode;
    public:
        explicit GenericExecutor (
                std::vector< vm_word > &bytecode, unsigned long maxMem
        ) : bytecode ( bytecode ){
            memory = new athena::core::Tensor* [maxMem];
        };

        void execute () override;

        void setMemoryCell ( unsigned long id, athena::core::Tensor* tensor ) override;

        athena::core::Tensor* getMemoryCell ( unsigned long id ) override;
    };
}


#endif //ATHENA_GENERICEXECUTOR_H
