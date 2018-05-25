//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_OPKERNEL_H
#define ATHENA_OPKERNEL_H

#include "opcodes.h"

namespace athena::core {
    class OpKernel {
    protected:
        OpCode opCode;
    public:
        explicit OpKernel(OpCode opCode) : opCode(opCode) {};
        virtual int getOperandsCount() = 0;
        virtual int* getOutputShape(int* shape, int dim) = 0;
    };
}


#endif //ATHENA_OPKERNEL_H
