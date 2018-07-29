//
// Created by Александр Баташев on 08.07.2018.
//

#include "AbstractMemoryManager.h"

void athena::backend::AbstractMemoryManager::resetTable () {
    tensors.clear();
}

void athena::backend::AbstractMemoryManager::addTensor ( athena::core::Tensor* tensor ) {
    tensors.push_back( tensor );
}

void
athena::backend::AbstractMemoryManager::loadAndLock ( athena::core::Tensor* tensor ) {
    loadAndLock( tensor->getStartAddress(), tensor->getShape().totalSize() *
                                            athena::core::typesize( tensor->getType()));
}

void athena::backend::AbstractMemoryManager::loadAndLock ( vm_word address ) {

    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            loadAndLock( t );
            break;
        }
    }

}

athena::core::Tensor*
athena::backend::AbstractMemoryManager::getTensor ( vm_word address ) {

    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            return t;
        }
    }

    return nullptr;
}

void
athena::backend::AbstractMemoryManager::allocateAndLock ( athena::core::Tensor* tensor ) {
    allocateAndLock( tensor->getStartAddress(),
                     athena::core::typesize( tensor->getType()) *
                     tensor->getShape().totalSize());
}

void athena::backend::AbstractMemoryManager::allocateAndLock ( vm_word address ) {
    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            allocateAndLock( t );
            break;
        }
    }
}
