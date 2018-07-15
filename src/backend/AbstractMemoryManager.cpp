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
athena::backend::AbstractMemoryManager::load ( athena::core::Tensor* tensor ) {
    load( tensor->getStartAddress(), tensor->getShape().total_size() *
                                     athena::core::typesize( tensor->getType()));
}

void athena::backend::AbstractMemoryManager::load ( vm_word address ) {

    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            load( t );
            break;
        }
    }

}
