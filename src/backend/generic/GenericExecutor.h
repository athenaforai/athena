//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_GENERICEXECUTOR_H
#define ATHENA_GENERICEXECUTOR_H

#include <backend/AbstractExecutor.h>
#include <stack>
#include <core/Tensor.h>
#include <vector>

namespace athena::backend::generic {
    class GenericExecutor : public athena::backend::AbstractExecutor {
    private:
        athena::core::Tensor& *memory;
        int *intRegisters;
        std::stack<int> intStack;

        std::vector<int> bytecode;
    public:
        explicit GenericExecutor(std::vector<int> bytecode, int maxMem) : bytecode(std::move(bytecode));
        void execute();
    };
}


#endif //ATHENA_GENERICEXECUTOR_H
