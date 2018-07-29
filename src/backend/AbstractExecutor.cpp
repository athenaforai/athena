//
// Created by Александр Баташев on 26.05.2018.
//

#include "AbstractExecutor.h"

void athena::backend::AbstractExecutor::setBytecode ( std::vector< vm_word > &bytecode ) {
    this->bytecode = bytecode;
}
