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

#ifndef ATHENA_ABSTRACTMEMORYMANAGER_H
#define ATHENA_ABSTRACTMEMORYMANAGER_H


#include <core/Tensor.h>
#include <list>

namespace athena::backend {

    /**
     * This class is an interface for physical memory managers. They provide
     * conversion between virtual addresses and physical ones. A typical strategy
     * for memory manager is to allocate as much memory as possible and then provide
     * tensors with it. This class also encapsulates table of athena::core::Tensor
     * objects. One can think of it as of variables table in a compiler.
     */
    class AbstractMemoryManager {
    protected:
        std::list< athena::core::Tensor* > tensors;

    public:

        virtual void init () = 0;
        virtual void deinit () = 0;

        /**
         * Clears table of Tensors
         */
        void resetTable ();

        /**
         * Adds Tensor to table
         * @param tensor Tensor, that will be added
         */
        void addTensor ( athena::core::Tensor* tensor );

        /**
         * Convert virtual address to physical one
         * @param virtualAddress Virtual address, unsigned long from 0 to 2^64-1
         * @return Pointer to physical memory
         */
        virtual void* getPhysicalAddress ( vm_word virtualAddress ) = 0;

        /**
         * Move data to the fastest memory type available (e.g. from hard drive to
         * RAM) and lock it (prevent from being offloaded)
         * @param tensor Tensor containing data
         */
        void loadAndLock ( athena::core::Tensor* tensor );

        /**
         * Move data to the fastest memory type available (e.g. from hard drive to
         * RAM) and lock it (prevent from being offloaded)
         * @param address Virtual address of Tensor containing data
         */
        void loadAndLock ( vm_word address );

        /**
         * Move data to the fastest memory type available (e.g. from hard drive to
         * RAM) and lock it (prevent from being offloaded)
         * @param address Virtual address
         * @param length Size of Tensor in bytes
         */
        virtual void loadAndLock ( vm_word address, unsigned long length ) = 0;

        /**
         * Lets data be offloaded to a slower memory type (e.g. from RAM to HDD)
         * @param address Virtual address
         */
        virtual void unlock ( vm_word address ) = 0;

        /**
         * Mark corresponding memory chunk as free
         * @param address Virtual address
         */
        virtual void deleteFromMem ( vm_word address ) = 0;

        athena::core::Tensor* getTensor ( vm_word address );

        /**
         * Allocate space in the fastest memory available without loading any data
         * and lock it (prevent from being offloaded)
         * @param tensor Tensor memory is being allocated for
         */
        void allocateAndLock( athena::core::Tensor* tensor );

        /**
         * Allocate space in the fastest memory available without loading any data
         * and lock it (prevent from being offloaded)
         * @param address Virtual address of Tensor memory is being allocated for
         */
        void allocateAndLock ( vm_word address );

        /**
         * Allocate space in the fastest memory available without loading any data
         * and lock it (prevent from being offloaded)
         * @param address Virtual address of Tensor memory is being allocated for
         * @param length Length in bytes for the piece of memory that is being allocated
         */
        virtual void allocateAndLock( vm_word address, unsigned long length ) = 0;

        /**
         * Sets memory with the data
         * @param tensorAddress Virtual address of Tensor beginning (see
         * Tensor::getStartAddress)
         * @param offset Offset in bytes from the beginning
         * @param length Length of piece of data in bytes
         * @param data Pointer to data
         */
        virtual void setData ( vm_word tensorAddress, vm_word offset, vm_word length,
                               void* data ) = 0;

        virtual void getData ( vm_word tensorAddress, vm_word offset, vm_word length,
                               void *data ) = 0;
    };
}


#endif //ATHENA_ABSTRACTMEMORYMANAGER_H
