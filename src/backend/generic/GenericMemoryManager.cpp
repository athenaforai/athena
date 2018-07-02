//
// Created by Александр Баташев on 27.06.2018.
//

#include "GenericMemoryManager.h"

void* athena::backend::generic::GenericMemoryManager::allocMemory (
        unsigned long threadId,
        unsigned long size
){
    return nullptr;
}

void athena::backend::generic::GenericMemoryManager::freeMemory (
        unsigned long threadId,
        unsigned long start,
        unsigned long end
){

}
