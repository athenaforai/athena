//
// Created by Александр Баташев on 27.06.2018.
//

#include "GenericMemoryManager.h"
#include <fstream>

void athena::backend::generic::GenericMemoryManager::init () {
    memory = malloc( allocatedMemory );


    laneFinished.push_back( false );
    std::thread thr( &GenericMemoryManager::processQueue, this, 0 );

    memLanes.push_back( thr );
}

void athena::backend::generic::GenericMemoryManager::processQueue ( int laneId ) {

    while ( !laneFinished[ laneId ] ) {
        // todo concurrency
        if ( !loadQueue.empty()) {
            auto item = loadQueue.front();
            loadQueue.pop();

            memoryChunksLock.lock();
            MemoryChunk* cur = memoryChunksHead;

            // select the first suitable memory chunk
            // todo better strategy to choose memory chunks
            while ( cur != nullptr && ( cur->length <= item->length || !cur->isFree )) {
                cur = cur->next;
            }

            if ( cur == nullptr ) {
                throw std::runtime_error( "Out of memory error!" );
            }
            if ( cur->length > item->length ) {
                auto newChunk = new MemoryChunk;
                newChunk->begin = cur->begin;
                newChunk->length = item->length;
                newChunk->virtualAddress = item->address;
                newChunk->prev = cur->prev;
                cur->prev->next = newChunk;

                auto freeChunk = new MemoryChunk;
                freeChunk->virtualAddress = 0;
                freeChunk->begin = newChunk->begin + newChunk->length;
                freeChunk->isFree = true;
                freeChunk->length = cur->length - newChunk->length;
                freeChunk->prev = newChunk;
                newChunk->next = freeChunk;
                freeChunk->next = cur->next;
                if ( cur->next != nullptr ) {
                    cur->next->prev = freeChunk;
                }

                cur = newChunk;
            }

            cur->isFree = false;
            cur->virtualAddress = item->address;

            if ( !item->alloc ) {
                for ( SwapRecord* record : swapRecords ) {
                    if ( record->address == item->address ) {
                        std::ifstream inp;
                        inp.open( record->filename );

                        inp.read( reinterpret_cast<char*>(cur->begin), cur->length );

                        inp.close();
                    }
                }
            }


            item->notified = true;
            item->loadHandle.notify_all();
        }
    }

}

void* athena::backend::generic::GenericMemoryManager::getPhysicalAddress (
        vm_word virtualAddress ) {

    MemoryChunk* cur = memoryChunksHead;
    while ( cur != nullptr ) {
        if ( cur->virtualAddress == virtualAddress ) {
            return cur->begin;
        }
        cur = cur->next;
    }

    return nullptr;
}

void athena::backend::generic::GenericMemoryManager::load ( vm_word address,
                                                            unsigned long length ) {

    auto item = new QueueItem();
    item->address = address;
    item->length = length;

    loadQueue.push( item );

    // See https://en.wikipedia.org/wiki/Spurious_wakeup for more info
    while ( !item->notified ) {
        item->loadHandle.wait( item->m );
    }

}

void athena::backend::generic::GenericMemoryManager::deinit () {
    for ( std::thread t : memLanes ) {
        t.join();
    }

    delete memory;
}

athena::backend::generic::GenericMemoryManager::~GenericMemoryManager () {
    deinit();
}

athena::backend::generic::GenericMemoryManager::GenericMemoryManager () = default;
