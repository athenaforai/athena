//
// Created by Александр Баташев on 27.06.2018.
//

#ifndef ATHENA_GENERICMEMORYMANAGER_H
#define ATHENA_GENERICMEMORYMANAGER_H


#include <backend/AbstractMemoryManager.h>
#include <thread>
#include <queue>
#include <condition_variable>
#include <thread>

namespace athena::backend::generic {

    struct SwapRecord {
        vm_word address;
        size_t length;
        std::string filename;
    };

    struct MemoryChunk {
        vm_word virtualAddress;
        void* begin;
        size_t length;
        bool isFree;
        MemoryChunk* next;
        MemoryChunk* prev;
    };

    struct QueueItem {
        vm_word address;
        size_t length;
        bool alloc = false;
        std::condition_variable loadHandle;
        std::unique_lock< std::mutex > m;
        bool notified = false;
    };

    class GenericMemoryManager : public AbstractMemoryManager {
    protected:
        std::list< SwapRecord* > swapRecords;
        MemoryChunk* memoryChunksHead;
        void* memory;

        std::unique_lock< std::mutex > memoryChunksLock;

        std::list< std::thread > memLanes;

        size_t allocatedMemory;

        std::queue< QueueItem* > loadQueue;

        std::vector< bool > laneFinished;

        void processQueue ( int laneId );

    public:

        GenericMemoryManager ();

        ~GenericMemoryManager ();

        void init ();

        void deinit ();

        void* getPhysicalAddress ( vm_word virtualAddress ) override;

        void load ( vm_word address, unsigned long length ) override;

    };
}


#endif //ATHENA_GENERICMEMORYMANAGER_H
