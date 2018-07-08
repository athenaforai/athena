//
// Created by Александр Баташев on 27.06.2018.
//

#ifndef ATHENA_GENERICMEMORYMANAGER_H
#define ATHENA_GENERICMEMORYMANAGER_H


#include <backend/AbstractMemoryManager.h>
#include <thread>

namespace athena::backend::generic {

    struct SwapRecord {
        vm_word address;
        size_t length;
        std::string filename;
    };

    struct MemoryChunk {
        vm_word virtualAddress;
        void * begin;
        size_t length;

    };

    class GenericMemoryManager : public AbstractMemoryManager {
    protected:
        std::list<SwapRecord*> swapRecords;
        std::list<MemoryChunk*> memoryChunks;
        void* memory;

        std::list<std::thread> memLanes;

        size_t allocatedMemory;

    public:

        void init();

    };
}


#endif //ATHENA_GENERICMEMORYMANAGER_H
