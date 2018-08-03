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
    if ( !isInitialized ) {
        memory = malloc( allocatedMemory );


        laneFinished.push_back( false );

        memLanes.push_back( new hermes::Thread(
                &GenericMemoryManager::allocationThreadFunc, this, 0 ));

        memoryChunksHead = new MemoryChunk;
        memoryChunksHead->virtualAddress = 0;
        memoryChunksHead->isFree = true;
        memoryChunksHead->isLocked = false;
        memoryChunksHead->begin = memory;
        memoryChunksHead->length = allocatedMemory;
        memoryChunksHead->next = nullptr;
        memoryChunksHead->prev = nullptr;

        isInitialized = true;
    }
}

void athena::backend::generic::GenericMemoryManager::allocationThreadFunc ( int laneId ) {

    while ( !laneFinished[ laneId ] ) {

        queueSemaphore.enter();
        queueMutex.lock();
        QueueItem* item = nullptr;
        if ( !loadQueue.empty()) {
            item = loadQueue.front();
            loadQueue.pop();
        }
        queueMutex.unlock();

        if ( item != nullptr ) {
            try {
                if ( item->type == QueueItemType::ALLOCATE ||
                     item->type == QueueItemType::LOAD ) {
                    allocateQueueItem( item );
                } else if ( item->type == QueueItemType::UNLOCK ) {
                    unlockQueueItem( item );
                } else if ( item->type == QueueItemType::DELETE ) {
                    deleteQueueItem( item );
                }
            } catch ( const std::exception &e ) {
            }

            item->notified = true;
            item->loadHandle.notifyAll();
        }

    }

}

void* athena::backend::generic::GenericMemoryManager::getPhysicalAddress (
        vm_word virtualAddress ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    memoryChunksLock.lock();
    MemoryChunk* cur = memoryChunksHead;
    while ( cur != nullptr ) {
        if ( cur->virtualAddress == virtualAddress ) {
            break;
        }
        cur = cur->next;
    }
    memoryChunksLock.unlock();

    return cur == nullptr ? nullptr : cur->begin;
}

void athena::backend::generic::GenericMemoryManager::loadAndLock ( vm_word address,
                                                                   unsigned long length ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    auto item = new QueueItem();
    item->address = address;
    item->length = length;
    item->type = QueueItemType::LOAD;

    pushQueueItem( item );

    item->loadHandle.wait( [ item ] () -> bool {
        return item->notified;
    } );

}

void athena::backend::generic::GenericMemoryManager::deinit () {
    if ( isInitialized ) {
        for ( auto &&i : laneFinished ) {
            i = true;
        }

        for ( int i = 0; i < memLanes.size(); i++ ) {
            queueSemaphore.leave();
        }

        for ( auto &memLane : memLanes ) {
            memLane->join();
        }

        memLanes.clear();
        laneFinished.clear();

        delete reinterpret_cast<u_char*>(memory);

        memory = nullptr;

        isInitialized = false;
    }
}

athena::backend::generic::GenericMemoryManager::~GenericMemoryManager () {
    deinit();
}

void athena::backend::generic::GenericMemoryManager::unlock ( vm_word address ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    auto item = new QueueItem;
    item->address = address;
    item->type = QueueItemType::UNLOCK;

    pushQueueItem( item );

    item->loadHandle.wait( [ item ] () -> bool {
        return item->notified;
    } );

}

void athena::backend::generic::GenericMemoryManager::deleteFromMem ( vm_word address ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    auto item = new QueueItem;
    item->address = address;
    item->type = QueueItemType::DELETE;

    pushQueueItem( item );

    item->loadHandle.wait( [ item ] () -> bool {
        return item->notified;
    } );

}

void athena::backend::generic::GenericMemoryManager::setMemSize ( size_t memSize ) {
    allocatedMemory = memSize;
}

void athena::backend::generic::GenericMemoryManager::allocateAndLock (
        vm_word address,
        unsigned long length ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    auto item = new QueueItem();
    item->address = address;
    item->length = length;
    item->type = QueueItemType::ALLOCATE;

    pushQueueItem( item );

    // See https://en.wikipedia.org/wiki/Spurious_wakeup for more info
    item->loadHandle.wait( [ item ] () -> bool {
        return item->notified;
    } );

}

void athena::backend::generic::GenericMemoryManager::setData ( vm_word tensorAddress,
                                                               vm_word offset,
                                                               vm_word length,
                                                               void* data ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    auto addr = reinterpret_cast<u_char*>(getPhysicalAddress( tensorAddress ));
    auto bData = reinterpret_cast<u_char*>(data);

    memcpy( addr + offset, bData, length );

}

void athena::backend::generic::GenericMemoryManager::getData ( vm_word tensorAddress,
                                                               vm_word offset,
                                                               vm_word length,
                                                               void* data ) {

    if ( !isInitialized ) {
        throw std::runtime_error( "GenericMemoryManager is not initialized" );
    }

    auto addr = reinterpret_cast<u_char*>(getPhysicalAddress( tensorAddress ));
    auto bData = reinterpret_cast<u_char*>(data);

    memcpy( bData, addr + offset, length );

}

void athena::backend::generic::GenericMemoryManager::allocateQueueItem (
        athena::backend::generic::QueueItem* item ) {

    MemoryChunk* cur = memoryChunksHead;

    // check if the element is already in the memory

    memoryChunksLock.lock();
    while ( cur != nullptr ) {
        if ( cur->virtualAddress == item->address ) {
            break;
        }
        cur = cur->next;
    }

    if ( cur != nullptr && !cur->isFree ) {
        cur->isLocked = true;
    }
    memoryChunksLock.unlock();
    if ( cur != nullptr ) {
        return;
    } else {

        cur = memoryChunksHead;

        // select the first suitable memory chunk
        // todo better strategy to choose memory chunks
        memoryChunksLock.lock();
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

        if ( item->type == QueueItemType::LOAD ) {
            for ( SwapRecord* record : swapRecords ) {
                if ( record->address == item->address ) {
                    std::ifstream inp;
                    inp.open( record->filename );

                    inp.read( reinterpret_cast<char*>(cur->begin), cur->length );

                    inp.close();
                }
            }
        }
    }
}

athena::backend::generic::GenericMemoryManager::GenericMemoryManager () {
    isInitialized = false;
    memory = nullptr;
    allocatedMemory = 0;
}

void athena::backend::generic::GenericMemoryManager::unlockQueueItem (
        athena::backend::generic::QueueItem* item ) {
    MemoryChunk* cur = memoryChunksHead;

    memoryChunksLock.lock();
    while ( cur != nullptr ) {
        if ( cur->virtualAddress == item->address ) {
            break;
        }
        cur = cur->next;
    }
    memoryChunksLock.unlock();

    if ( cur != nullptr ) {

        if ( cur->hasChanged ) {
            SwapRecord* record = nullptr;

            for ( SwapRecord* r : swapRecords ) {
                if ( r->address == item->address ) {
                    record = r;
                    break;
                }
            }

            if ( record == nullptr ) {
                record = new SwapRecord;
                record->address = item->address;
                record->length = cur->length;
                record->filename = std::to_string( item->address ) + ".swap";

                swapRecords.push_back( record );
            }

            std::ofstream ofs( record->filename );
            ofs.write( reinterpret_cast<char*>(cur->begin), cur->length );
            ofs.close();

            cur->hasChanged = false;
        }

        memoryChunksLock.lock();
        cur->isLocked = false;
        memoryChunksLock.unlock();
    }
}

void athena::backend::generic::GenericMemoryManager::deleteQueueItem (
        athena::backend::generic::QueueItem* item ) {

    MemoryChunk* cur = memoryChunksHead;

    memoryChunksLock.lock();
    while ( cur != nullptr ) {
        if ( cur->virtualAddress == item->address ) {
            break;
        }
        cur = cur->next;
    }

    if ( cur != nullptr ) {
        cur->isFree = true;
        cur->isLocked = false;

        if ( cur->next != nullptr && cur->next->isFree ) {
            cur->length += cur->next->length;

            MemoryChunk* tmp = cur->next;

            cur->next = tmp->next;
            if ( tmp->next != nullptr ) {
                tmp->next->prev = cur;
            }

            tmp->next = nullptr;
            tmp->prev = nullptr;
            delete tmp;
        }

        if ( cur->prev != nullptr && cur->prev->isFree ) {
            cur->length += cur->prev->length;

            MemoryChunk* tmp = cur->prev;

            cur->prev = tmp->prev;
            if ( tmp->prev != nullptr ) {
                tmp->prev->next = cur;
            }

            tmp->next = nullptr;
            tmp->prev = nullptr;

            delete tmp;
        }
    }

    memoryChunksLock.unlock();

}

void athena::backend::generic::GenericMemoryManager::pushQueueItem (
        athena::backend::generic::QueueItem* item ) {

    queueMutex.lock();
    loadQueue.push( item );
    queueMutex.unlock();
    queueSemaphore.leave();

}
