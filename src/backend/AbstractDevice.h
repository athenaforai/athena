//
// Created by Александр Баташев on 27.06.2018.
//

#ifndef ATHENA_ABSTRACTDEVICE_H
#define ATHENA_ABSTRACTDEVICE_H

namespace athena::backend {
    class AbstractDevice {
    protected:
        unsigned long maxThreadMemorySize;
        unsigned long maxThreads;
        unsigned long memorySize;
    public:
        unsigned long getMaxThreadMemSize ();

        void setMaxThreadMemSize ( unsigned long size = 0 );
    };
}


#endif //ATHENA_ABSTRACTDEVICE_H
