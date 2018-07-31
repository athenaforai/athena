/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaproject.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include "GenericMemoryManager.h"
#include <fstream>
#include <cstring>

void athena::backend::generic::GenericMemoryManager::init () {
    memory = malloc( allocatedMemory );


    laneFinished.push_back( false );
    std::thread thr( &GenericMemoryManager::allocationThreadFunc, this, 0 );

    memLanes.push_back( std::move( thr ));

    memoryChunksHead = new MemoryChunk;
    memoryChunksHead->virtualAddress = 0;
    memoryChunksHead->isFree = true;
    memoryChunksHead->isLocked = false;
    memoryChunksHead->begin = memory;
    memoryChunksHead->length = allocatedMemory;
    memoryChunksHead->next = nullptr;
    memoryChunksHead->prev = nullptr;
}

void athena::backend::generic::GenericMemoryManager::allocationThreadFunc ( int laneId ) {

    while ( !laneFinished[ laneId ] ) {
        // todo concurrency
        if ( !loadQueue.empty()) {
            auto item = loadQueue.front();
            loadQueue.pop();

            processQueueItem( item );
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

void athena::backend::generic::GenericMemoryManager::loadAndLock ( vm_word address,
                                                                   unsigned long length ) {

    auto item = new QueueItem();
    item->address = address;
    item->length = length;

    loadQueue.push( item );

    std::mutex m;
    std::unique_lock< std::mutex > lock( m );

    // See https://en.wikipedia.org/wiki/Spurious_wakeup for more info
    // todo this is temp fix for https://github.com/athenaml/athena/issues/7
#ifdef __APPLE__
    item->loadHandle.wait_for( lock, std::chrono::seconds( 3 ), [ item ] {
        return !item->notified;
    } );
#else
    item->loadHandle.wait(lock, [item]{ return !item->notified; } );
#endif
    lock.unlock();

}

void athena::backend::generic::GenericMemoryManager::deinit () {
    for ( auto &&i : laneFinished ) {
        i = true;
    }

    for ( auto &memLane : memLanes ) {
        memLane.join();
    }

    memLanes.clear();
    laneFinished.clear();

    delete reinterpret_cast<u_char*>(memory);

    memory = nullptr;
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

    memoryChunksLock.unlock();

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
        record->filename = std::to_string( address ) + ".swap"; // todo unique names

        swapRecords.push_back( record );
    }

    std::ofstream ofs( record->filename );
    ofs.write( reinterpret_cast<char*>(cur->begin), cur->length );
    ofs.close();

    memoryChunksLock.lock();
    cur->isLocked = false;
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

void athena::backend::generic::GenericMemoryManager::allocateAndLock (
        vm_word address,
        unsigned long length ) {

    auto item = new QueueItem();
    item->address = address;
    item->length = length;
    item->alloc = true;

    loadQueue.push( item );

    std::mutex m;
    std::unique_lock< std::mutex > lock( m );

    // See https://en.wikipedia.org/wiki/Spurious_wakeup for more info
    // todo this is temp fix for https://github.com/athenaml/athena/issues/7
#ifdef __APPLE__
    item->loadHandle.wait_for( lock, std::chrono::seconds( 3 ), [ item ] {
        return !item->notified;
    } );
#else
    item->loadHandle.wait(lock, [item]{ return !item->notified; } );
#endif

    lock.unlock();

}

void athena::backend::generic::GenericMemoryManager::setData ( vm_word tensorAddress,
                                                               vm_word offset,
                                                               vm_word length,
                                                               void* data ) {

    auto addr = reinterpret_cast<u_char*>(getPhysicalAddress( tensorAddress ));
    auto bData = reinterpret_cast<u_char*>(data);

    memcpy( addr + offset, bData, length );

}

void athena::backend::generic::GenericMemoryManager::getData ( vm_word tensorAddress,
                                                               vm_word offset,
                                                               vm_word length,
                                                               void* data ) {

    auto addr = reinterpret_cast<u_char*>(getPhysicalAddress( tensorAddress ));
    auto bData = reinterpret_cast<u_char*>(data);

    memcpy( bData, addr + offset, length );

}

void athena::backend::generic::GenericMemoryManager::processQueueItem (
        athena::backend::generic::QueueItem* item ) {
    memoryChunksLock.lock();
    MemoryChunk* cur = memoryChunksHead;

    // check if the element is already in the memory

    while ( cur != nullptr ) {
        if ( cur->virtualAddress == item->address ) {
            break;
        }
        cur = cur->next;
    }

    if ( cur != nullptr ) {
        cur->isLocked = true;

        memoryChunksLock.unlock();

        item->notified = true;
        item->loadHandle.notify_all();

    } else {

        cur = memoryChunksHead;

        // select the first suitable memory chunk
        // todo better strategy to choose memory chunks
        //TODO CHECK CONDITION IN WHILE(...)
        while ( cur != nullptr &&
                ( cur->length <= item->length
                  && ( !cur->isFree || !cur->isLocked ))) {
            cur = cur->next;
        }

        if ( cur == nullptr ) {
            throw std::runtime_error( "Out of memory error!" );
        }
        if ( cur->length > item->length ) {     //TODO BUT IF IT FALSE?
            auto newChunk = new MemoryChunk;
            newChunk->begin = cur->begin;
            newChunk->length = item->length;
            newChunk->virtualAddress = item->address;
            newChunk->prev = cur->prev;

            if ( cur->prev != nullptr ) {
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

            if ( cur == memoryChunksHead ) {
                memoryChunksHead = newChunk;
            }

            cur->prev = nullptr;
            cur->next = nullptr;
            delete cur;

            cur = newChunk;
        }

        cur->isFree = false;
        cur->isLocked = true;
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

athena::backend::generic::GenericMemoryManager::GenericMemoryManager () = default;
