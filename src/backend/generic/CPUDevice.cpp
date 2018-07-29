//
// Created by Александр Баташев on 27.06.2018.
//

#include "CPUDevice.h"
#include <thread>

athena::backend::generic::CPUDevice::CPUDevice () : AbstractDevice() {
    maxThreads = std::thread::hardware_concurrency();
    activeThreads = 0;
    memorySize = 1024 * 1024 * 1024; // 1 GB todo replace with real mem size
    memoryManager = new GenericMemoryManager();
    memoryManager->setMemSize( memorySize );
}

athena::backend::AbstractMemoryManager*
athena::backend::generic::CPUDevice::getMemoryManager () {
    return memoryManager;
}
