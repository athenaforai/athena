//
// Created by Александр Баташев on 08.07.2018.
//

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

        void load ( athena::core::Tensor* tensor );

        void load ( vm_word address );

        /**
         * Move data to the fastest memory type available (e.g. from hard drive to
         * RAM) and lock it (prevent from being offloaded)
         * @param address Virtual address
         * @param length Size of Tensor in bytes
         */
        virtual void load ( vm_word address, unsigned long length ) = 0;

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

    };
}


#endif //ATHENA_ABSTRACTMEMORYMANAGER_H
