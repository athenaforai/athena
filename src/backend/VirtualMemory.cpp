//
// Created by Александр Баташев on 08.07.2018.
//

#include "VirtualMemory.h"
#include <core/DataType.h>

athena::backend::VirtualMemory::VirtualMemory () {
    head = new VMemoryBlock;
    head->isUsed = false;
    head->startAddress = 1;
    head->endAddress = LONG_MAX;
    head->nextBlock = nullptr;

    maxMemoryUsage = 0;
    curMemoryUsage = 0;
}

void athena::backend::VirtualMemory::allocate ( athena::core::Tensor* tensor ) {
    VMemoryBlock* cur = head;

    unsigned long memNeeded = tensor->getShape().total_size() *
                              athena::core::typesize( tensor->getType());

    bool allocated = false;

    while ( cur != nullptr && !allocated ) {
        if ( !cur->isUsed && (cur->endAddress - cur->startAddress) >= memNeeded ) {
            auto newUsedBlock = new VMemoryBlock;
            newUsedBlock->isUsed = true;
            newUsedBlock->startAddress = cur->startAddress;
            newUsedBlock->endAddress = newUsedBlock->startAddress + memNeeded;
            newUsedBlock->prevBlock = cur->prevBlock;

            if ( cur->endAddress - cur->startAddress > memNeeded ) {
                auto freeBlock = new VMemoryBlock;
                freeBlock->isUsed = false;
                freeBlock->startAddress = newUsedBlock->endAddress;
                freeBlock->endAddress = cur->endAddress;
                freeBlock->nextBlock = cur->nextBlock;
                freeBlock->prevBlock = newUsedBlock;

                newUsedBlock->nextBlock = freeBlock;
            } else {
                newUsedBlock->nextBlock = cur->nextBlock;
            }

            allocated = true;
            curMemoryUsage += memNeeded;
            if ( curMemoryUsage > maxMemoryUsage ) {
                maxMemoryUsage = curMemoryUsage;
            }

            cur->nextBlock = nullptr;
            cur->prevBlock = nullptr;
            delete cur;
        } else {
            cur = cur->nextBlock;
        }
    }

    if ( !allocated ) {
        throw std::runtime_error( "OutOfMemory error" );
    }



}

void athena::backend::VirtualMemory::free ( vm_word virtualAddress ) {

    VMemoryBlock *cur = head;

    bool found = false;

    while ( cur != nullptr && !found ) {
        if ( cur->startAddress == virtualAddress ) {
            cur->isUsed = false;
            curMemoryUsage -= cur->endAddress - cur->startAddress;

            // merge two free blocks
            if ( cur->nextBlock != nullptr && !cur->nextBlock->isUsed ) {
                VMemoryBlock *old = cur->nextBlock;

                cur->endAddress = old->endAddress;
                if ( old->nextBlock != nullptr ) {
                    old->nextBlock->prevBlock = cur;
                }
                cur->nextBlock = old->nextBlock;

                old->nextBlock = nullptr;
                old->prevBlock = nullptr;
                delete old;
            }

            found = true;
        } else {
            cur = cur->nextBlock;
        }
    }
}

void athena::backend::VirtualMemory::free ( athena::core::Tensor* tensor ) {
//    free()
}

