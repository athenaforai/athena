/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaframework.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
#include "VirtualMemory.h"
#include <core/DataType.h>

athena::backend::VirtualMemory::VirtualMemory () {
    head = new VMemoryBlock;
    head->isUsed = false;
    head->startAddress = 1;
    head->endAddress = LONG_MAX;
    head->nextBlock = nullptr;
    head->prevBlock = nullptr;

    maxMemoryUsage = 0;
    curMemoryUsage = 0;
}

vm_word athena::backend::VirtualMemory::allocate ( athena::core::Tensor* tensor ) {
    VMemoryBlock* cur = head;

    unsigned long memNeeded = tensor->getShape().totalSize() *
                              athena::core::typesize( tensor->getType());

    bool allocated = false;

    while ( cur != nullptr && !allocated ) {
        if ( !cur->isUsed && (cur->endAddress - cur->startAddress) >= memNeeded ) {
            auto newUsedBlock = new VMemoryBlock;
            newUsedBlock->isUsed = true;
            newUsedBlock->startAddress = cur->startAddress;
            newUsedBlock->endAddress = newUsedBlock->startAddress + memNeeded;
            newUsedBlock->prevBlock = cur->prevBlock;

            if ( cur->prevBlock != nullptr ) {
                cur->prevBlock->nextBlock = newUsedBlock;
            }

            if ( cur->endAddress - cur->startAddress > memNeeded ) {
                auto freeBlock = new VMemoryBlock;
                freeBlock->isUsed = false;
                freeBlock->startAddress = newUsedBlock->endAddress;
                freeBlock->endAddress = cur->endAddress;
                freeBlock->nextBlock = cur->nextBlock;
                freeBlock->prevBlock = newUsedBlock;

                newUsedBlock->nextBlock = freeBlock;

                if ( cur->nextBlock != nullptr ) {
                    cur->nextBlock->prevBlock = freeBlock;
                }
            } else {
                newUsedBlock->nextBlock = cur->nextBlock;
                if ( cur->nextBlock != nullptr ) {
                    cur->nextBlock->prevBlock = newUsedBlock;
                }
            }

            allocated = true;
            curMemoryUsage += memNeeded;
            if ( curMemoryUsage > maxMemoryUsage ) {
                maxMemoryUsage = curMemoryUsage;
            }

            cur->nextBlock = nullptr;
            cur->prevBlock = nullptr;
            if ( cur == head ) {
                head = newUsedBlock;
            }
            delete cur;
            cur = newUsedBlock;
        } else {
            cur = cur->nextBlock;
        }
    }

    if ( !allocated ) {
        throw std::runtime_error( "OutOfMemory error" );
    }

    tensor->setStartAddress( cur->startAddress );

    tensors.push_back( tensor );

    return cur->startAddress;
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

    for ( unsigned long i = 0; i < tensors.size(); i++ ) {
        if ( tensors[ i ]->getStartAddress() == virtualAddress ) {
            tensors.erase( tensors.begin() + i );
            break;
        }
    }
}

void athena::backend::VirtualMemory::free ( athena::core::Tensor* tensor ) {
    free( tensor->getStartAddress());
}

athena::core::Tensor* athena::backend::VirtualMemory::getTensor ( vm_word address ) {
    for ( auto &tensor : tensors ) {
        if ( tensor->getStartAddress() == address ) {
            return tensor;
        }
    }
    return nullptr;
}

