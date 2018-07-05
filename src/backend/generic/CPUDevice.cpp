//
// Created by Александр Баташев on 27.06.2018.
//

#include "CPUDevice.h"
#include <thread>

athena::backend::generic::CPUDevice::CPUDevice () : AbstractDevice() {
    maxThreads = std::thread::hardware_concurrency();
    activeThreads = 0;
    memoryManager = new GenericMemoryManager();
}
