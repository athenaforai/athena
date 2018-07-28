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
#include <string>

namespace athena::backend::generic {

    /**
     * Describes single swap record - a file, that stores Tensor data
     */
    struct SwapRecord {
        vm_word address;
        size_t length;
        std::string filename;
    };

    /**
     * Describes single memory chunk that is allocated in RAM.
     * Free status means there is no data in this chunk
     * Locked status means this chunk is being used now and can't be unload to
     * persistent memory.
     */
    struct MemoryChunk {
        vm_word virtualAddress;
        void* begin;
        size_t length;
        bool isFree;
        bool isLocked;
        MemoryChunk* next;
        MemoryChunk* prev;
    };

    /**
     * Describes which Tensors should be loaded to RAM
     * Alloc flag means we should not search for data in Swap
     */
    struct QueueItem {
        vm_word address;
        size_t length;
        bool alloc = false;
        std::condition_variable loadHandle;
        std::mutex m;
        bool notified = false;
    };

    /**
     * This class implements AbstractMemoryManager interface for
     * GenericExecutor. It pre-allocates RAM and uses persistent memory for
     * swap. There are couple memory lanes - threads, that manage RAM.
     * They monitor loadQueue for new queries and move data from hard drive
     * to RAM if needed.
     */
    class GenericMemoryManager : public AbstractMemoryManager {
    protected:
        std::list< SwapRecord* > swapRecords;
        MemoryChunk* memoryChunksHead;
        void* memory;

        std::mutex memoryChunksLock;

        std::vector< std::thread > memLanes;

        size_t allocatedMemory;

        std::queue< QueueItem* > loadQueue;

        std::vector< bool > laneFinished;

        // хранит список загруженных тензоров, скорее всего костыль
        std::vector<vm_word> lockedList;

        /**
         * This is a thread function for memory lane-threads. It loads data to
         * RAM and notifies corresponding threads
         * @param laneId
         */
        void processQueue ( int laneId );

    public:

        GenericMemoryManager ();

        ~GenericMemoryManager ();

        /**
         * Initialize memory manager. That's where actual memory allocation
         * happens. All configurations should be done before this method is called.
         */
        void init () override;

        /**
         * Free RAM and stop all threads-memory lanes
         */
        void deinit () override;

        /**
         * Convert virtual address to physical one
         * @param virtualAddress Virtual address, unsigned long from 0 to 2^64-1
         * @return Pointer to physical memory
         */
        void* getPhysicalAddress ( vm_word virtualAddress ) override;

        void loadAndLock ( vm_word address, unsigned long length ) override;

        using AbstractMemoryManager::loadAndLock;

        void allocateAndLock ( vm_word address, unsigned long length ) override;

        using AbstractMemoryManager::allocateAndLock;

        void unlock ( vm_word address ) override;

        void deleteFromMem ( vm_word address ) override;

        void setMemSize( size_t memSize );

        void setData ( vm_word tensorAddress, vm_word offset, vm_word length,
                       void* data ) override;

        void getData ( vm_word tensorAddress, vm_word offset, vm_word length,
                       void* data ) override;
    };
}


#endif //ATHENA_GENERICMEMORYMANAGER_H
