//
// Created by Александр Баташев on 20.07.2018.
//

#include "DataInitializer.h"

void athena::core::initializers::DataInitializer::initialize (
        athena::backend::AbstractMemoryManager* manager,
        athena::core::Tensor* tensor ) {

    manager->allocateAndLock( tensor );
    manager->setData( tensor->getStartAddress(), 0, length, data );
    manager->unlock( tensor->getStartAddress());

}

athena::core::initializers::DataInitializer::DataInitializer (
        const athena::core::initializers::DataInitializer &src ) {
    this->data = src.data;
}

athena::core::initializers::DataInitializer &
athena::core::initializers::DataInitializer::operator= (
        const athena::core::initializers::DataInitializer &src ) {
    this->data = src.data;
    return *this;
}

athena::core::initializers::DataInitializer::~DataInitializer () {
    data = nullptr;
}

void athena::core::initializers::DataInitializer::setData ( void* ptr, size_t length ) {
    this->data = ptr;
    this->length = length;
}
