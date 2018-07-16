//
// Created by Александр Баташев on 26.05.2018.
//

#ifndef ATHENA_EXECUTORSERVICE_H
#define ATHENA_EXECUTORSERVICE_H

#include <utility>
#include <vector>
#include <core/Tensor.h>
#include "AbstractExecutor.h"
#include "generic/GenericExecutor.h"

//namespace athena::backend {
//    class ExecutorService {
//    private:
//        std::vector< vm_word > &bytecode;
//        unsigned long maxMem;
//        unsigned long resultCell;
//
//        AbstractExecutor* executor;
//    public:
//        ExecutorService (
//                std::vector< vm_word > &bytecode, unsigned long maxMem,
//                unsigned long resultCell
//        ) :
//                bytecode( bytecode ), maxMem( maxMem ), resultCell( resultCell ) {
//            executor = new athena::backend::generic::GenericExecutor(
//                    this->bytecode, maxMem
//            );
//        };
//
//        void setMemoryCell ( unsigned long id, athena::core::Tensor* tensor );
//
//        athena::core::Tensor* execute ();
//
//        void setBytecode(std::vector< vm_word > &bytecode);
//    };
//}


#endif //ATHENA_EXECUTORSERVICE_H
