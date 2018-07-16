//
// Created by Александр Баташев on 27.06.2018.
//

#ifndef ATHENA_CPUDEVICE_H
#define ATHENA_CPUDEVICE_H


#include <backend/AbstractDevice.h>
#include "GenericMemoryManager.h"

namespace athena::backend::generic {

    /**
     * This class represents a CPU
     * It encapsulates Memory Manager
     */
    class CPUDevice : public AbstractDevice {
    private:
        unsigned long activeThreads;
        GenericMemoryManager* memoryManager;
    public:
        CPUDevice ();

        AbstractMemoryManager* getMemoryManager() override ;

    };
}


#endif //ATHENA_CPUDEVICE_H
