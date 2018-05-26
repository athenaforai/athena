//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_OPKERNEL_H
#define ATHENA_OPKERNEL_H

#include <string>
#include "opcodes.h"

namespace athena::core {
    /**
     * Operation skeleton
     * Each operation has OpCode
     */
    class OpKernel {
    protected:
        OpCode opCode;
        std::string name;
    public:
        explicit OpKernel(OpCode opCode, std::string_view name) : opCode(opCode), name(name) {};

        /**
         * There can be unary, binary and other operations
         * @return Number of operands accepted
         */
        virtual int getOperandsCount() = 0;

        /**
         * It is important for some operations to have
         * certain size of their operands
         * @param shape Original operand shape
         * @param dim Dimensionality
         * @return New shape
         */
        virtual int *getOutputShape(int *shape, int dim) = 0;

        virtual std::vector<int> getOpBytecode(std::vector<int> args) = 0;
    };
}


#endif //ATHENA_OPKERNEL_H
