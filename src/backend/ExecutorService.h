//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_EXECUTORSERVICE_H
#define ATHENA_EXECUTORSERVICE_H

#include <utility>
#include <vector>
#include <core/Tensor.h>

namespace athena::backend {
    class ExecutorService {
    private:
        std::vector<int> bytecode;
        unsigned long maxMem;
        unsigned long resultCell;
    public:
        ExecutorService(std::vector<int> bytecode, unsigned long maxMem, unsigned long resultCell) :
                bytecode(std::move(bytecode)), maxMem(maxMem), resultCell(resultCell) {};

        template <typename T>
        void setMemoryCell(unsigned long id, athena::core::Tensor<T>* tensor) {

        }
    };
}


#endif //ATHENA_EXECUTORSERVICE_H
