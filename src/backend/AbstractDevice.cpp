//
// Created by Александр Баташев on 27.06.2018.
//

#include "AbstractDevice.h"

unsigned long athena::backend::AbstractDevice::getMaxThreadMemSize () {
    return maxThreadMemorySize;
}

void athena::backend::AbstractDevice::setMaxThreadMemSize ( unsigned long size ) {
    if ( size == 0 ) {
        maxThreadMemorySize = memorySize / maxThreads;
    }
}
