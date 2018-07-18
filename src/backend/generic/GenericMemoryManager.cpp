//
// Created by Александр Баташев on 27.06.2018.
//

#include "GenericMemoryManager.h"
#include <fstream>

void athena::backend::generic::GenericMemoryManager::init () {
    memory = malloc( allocatedMemory );


    laneFinished.push_back( false );
    std::thread thr( &GenericMemoryManager::processQueue, this, 0 );

    memLanes.push_back( std::move( thr ));

    memoryChunksHead = new MemoryChunk;
    memoryChunksHead->isFree = true;
    memoryChunksHead->isLocked = false;
    memoryChunksHead->begin = memory;
    memoryChunksHead->length = allocatedMemory;
    memoryChunksHead->next = nullptr;
    memoryChunksHead->prev = nullptr;
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
            while ( cur != nullptr &&
                    ( cur->length <= item->length
                      && ( !cur->isFree || !cur->isLocked ))) {
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

                if (cur->prev != nullptr) {
                    cur->prev->next = newChunk;
                }

                auto freeChunk = new MemoryChunk;
                freeChunk->virtualAddress = 0;
                freeChunk->begin = reinterpret_cast<char*>(newChunk->begin) +
                                   newChunk->length;
                freeChunk->isFree = true;
                freeChunk->length = cur->length - newChunk->length;
                freeChunk->prev = newChunk;
                newChunk->next = freeChunk;
                freeChunk->next = cur->next;
                if ( cur->next != nullptr ) {
                    cur->next->prev = freeChunk;
                }

                cur = newChunk;
                if ( cur == memoryChunksHead ) {
                    memoryChunksHead = newChunk;
                }

                cur->prev = nullptr;
                cur->next = nullptr;
                delete cur;
            }

            cur->isFree = false;
            cur->virtualAddress = item->address;

            memoryChunksLock.unlock();

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

    std::mutex m;
    std::unique_lock< std::mutex > lock( m );

    // See https://en.wikipedia.org/wiki/Spurious_wakeup for more info
    while ( !item->notified ) {

//        item->m = std::move(m);

        item->loadHandle.wait( lock );
    }

}

void athena::backend::generic::GenericMemoryManager::deinit () {
    for ( int i = 0; i < memLanes.size(); i++ ) {
        memLanes[ i ].join();
    }

    delete memory;
}

athena::backend::generic::GenericMemoryManager::~GenericMemoryManager () {
    deinit();
}

void athena::backend::generic::GenericMemoryManager::unlock ( vm_word address ) {
    memoryChunksLock.lock();

    auto cur = memoryChunksHead;

    while ( cur != nullptr && cur->virtualAddress == address ) {
        cur = cur->next;
    }

    if ( cur == nullptr ) {
        throw std::runtime_error( "Address not found" );
    }


    cur->isLocked = false;
    SwapRecord* record = nullptr;

    for ( SwapRecord* r : swapRecords ) {
        if ( r->address == address ) {
            record = r;
            break;
        }
    }

    if ( record == nullptr ) {
        record = new SwapRecord;
        record->address = address;
        record->length = cur->length;
        record->filename = "0.swap"; // todo unique names

        swapRecords.push_back( record );
    }

    std::ofstream ofs( record->filename );
    ofs.write( reinterpret_cast<char*>(cur->begin), cur->length );
    ofs.close();

    memoryChunksLock.unlock();
}

void athena::backend::generic::GenericMemoryManager::deleteFromMem ( vm_word address ) {

    memoryChunksLock.lock();

    auto cur = memoryChunksHead;

    while ( cur != nullptr && cur->virtualAddress == address ) {
        cur = cur->next;
    }

    if ( cur == nullptr ) {
        return;
    }

    // todo remove swap records, merge memory chunks

    cur->isFree = true;

    memoryChunksLock.unlock();

}

void athena::backend::generic::GenericMemoryManager::setMemSize ( size_t memSize ) {
    allocatedMemory = memSize;
}

athena::backend::generic::GenericMemoryManager::GenericMemoryManager () = default;
