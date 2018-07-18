//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_OPKERNEL_H
#define ATHENA_OPKERNEL_H

#include <string>
#include <utility>
#include <vector>

#include "opcodes.h"
#include <core/TensorShape.h>

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
        explicit OpKernel ( OpCode opCode, std::string name ) :
                opCode( opCode ), name( std::move( name )) {};

        /**
         * There can be unary, binary and other operations
         * @return Number of operands accepted
         */
        virtual int getOperandsCount () = 0;

        /**
         * It is important for some operations to have
         * certain size of their operands
         * @param shape Original operand shape
         * @param dim Dimensionality
         * @return New shape
         */
        virtual athena::core::TensorShape &getOutputShape (
                std::vector< athena::core::TensorShape > &shapes ) = 0;

        /**
         * It is important for some operations to have
         * certain size of their operands
         * @param shape Original operand shape
         * @param dim Dimensionality
         * @return New shape
         */
        virtual athena::core::TensorShape &getDerivativeShape (
                int d,
                std::vector< athena::core::TensorShape > &shapes ) = 0;

        virtual std::vector< vm_word >
        getOpBytecode ( std::vector< vm_word > args, vm_word resultCell ) = 0;

        /**
         * Generates bytecode to calculate partial derivative
         * @param d Number of variable with respect to which derivative is calculated
         * @param args Function arguments
         * @param resultCell Number of memory cell where results are saved
         * @return
         */
        virtual std::vector< vm_word > getDerivativeBytecode (
                int d, std::vector< vm_word > args,
                vm_word resultCell
        ) = 0;
    };
}


#endif //ATHENA_OPKERNEL_H
