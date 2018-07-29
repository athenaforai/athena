//
// Created by Александр Баташев on 26.05.2018.
//
#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include "GenericMemoryManager.h"

namespace athena::backend::generic {

    void addf ( GenericMemoryManager* memoryManager,
                                 athena::core::Tensor* a,
                                 athena::core::Tensor* b,
                                 athena::core::Tensor* res ) {
        // todo find optimizations
        auto af = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < b->getShape().dim( 0 ); i++ ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
    }

    void addd ( GenericMemoryManager* memoryManager,
                                 athena::core::Tensor* a,
                                 athena::core::Tensor* b,
                                 athena::core::Tensor* res ) {
        auto af = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < b->getShape().dim( 0 ); i++ ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
    }

    void addi ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* a,
                athena::core::Tensor* b,
                athena::core::Tensor* res ) {
        auto af = reinterpret_cast<int*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<int*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<int*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < b->getShape().dim( 0 ); i++ ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
    }

    void add ( GenericMemoryManager* memoryManager,
                                athena::core::Tensor* a,
                                athena::core::Tensor* b,
                                athena::core::Tensor* res
    ) {

        if ( a->getShape() == b->getShape()) {
            switch ( a->getType()) {
                case athena::core::DataType::FLOAT:
                    addf( memoryManager, a, b, res );
                    break;
                case athena::core::DataType::DOUBLE:
                    addd( memoryManager, a, b, res );
                    break;
                case athena::core::DataType::INT:
                    addi( memoryManager, a, b, res );
                    break;
            }
        }
    }
}