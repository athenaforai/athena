//
// Created by Александр Баташев on 26.05.2018.
//

#include "ExecutorService.h"

void athena::backend::ExecutorService::setMemoryCell (
        unsigned long id, athena::core::Tensor* tensor
) {
    executor->setMemoryCell ( id, tensor );
}

athena::core::Tensor* athena::backend::ExecutorService::execute () {
    executor->execute ();
    return executor->getMemoryCell ( resultCell );
}
