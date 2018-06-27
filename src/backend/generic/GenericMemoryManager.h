//
// Created by Александр Баташев on 27.06.2018.
//

#ifndef ATHENA_GENERICMEMORYMANAGER_H
#define ATHENA_GENERICMEMORYMANAGER_H


namespace athena::backend::generic {
    class GenericMemoryManager {
    public:
        void* allocMemory(unsigned long threadId, unsigned long size);

        void freeMemory(unsigned long threadId, unsigned long start, unsigned long end);
    };
}


#endif //ATHENA_GENERICMEMORYMANAGER_H
