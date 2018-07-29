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

#ifndef ATHENA_VIRTUALMEMORY_H
#define ATHENA_VIRTUALMEMORY_H

#include <core/Tensor.h>
#include <core/opcodes.h>
#include <climits>

namespace athena::backend {

    struct VMemoryBlock {
        bool isUsed;
        vm_word startAddress;
        vm_word endAddress;
        VMemoryBlock* nextBlock;
        VMemoryBlock* prevBlock;
    };

    /**
     * Virtual memory is an abstraction of storage resources that are actually
     * available on a given machine. Each thread has its own address space.
     * In Athena's VM address space is linear. This means that valid addresses
     * are 0 to 2^64 - 1. Address 0 is reserved for NULL value. When Tensor is
     * initialized, it is given with a continuous block of virtual addresses.
     * When one actually needs to access Tensor's data, Memory Manager allocates
     * physical memory and converts virtual addresses to physical ones. This helps
     * Athena to run in low-memory conditions. This class is heavily used in
     * Session class to generate bytecode.
     * <br/>
     * To discover more about Virtual Memory see article on
     * <a href="https://en.wikipedia.org/wiki/Virtual_memory">Wikipedia</a>
     */
    class VirtualMemory {
    private:
        VMemoryBlock* head;
        /**
         * Accumulates max memory usage at particular time spot in bytes
         * This value will be used to determine max thread count
         */
        size_t maxMemoryUsage;

        size_t curMemoryUsage;

        std::vector<athena::core::Tensor*> tensors;

    public:

        VirtualMemory ();

        /**
         * Allocates virtual memory for given Tensor
         * @param tensor Tensor object
         * @return Virtual Address of 0 element of Tensor
         */
        vm_word allocate ( athena::core::Tensor* tensor );

        /**
         * Marks memory as free
         * @param tensor Corresponding tensor
         */
        void free ( athena::core::Tensor* tensor );

        /**
         * Marks memory as free
         * @param virtualAddress
         */
        void free ( vm_word virtualAddress );

        athena::core::Tensor* getTensor ( vm_word address );
    };
}


#endif //ATHENA_VIRTUALMEMORY_H
