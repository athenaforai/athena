//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_OPCODES_H
#define ATHENA_OPCODES_H

typedef unsigned long vm_word;

enum class OpCode : vm_word {
    DEL = 0x00,
    PUSH = 0x01,
    POP = 0x02,
    JMP = 0x03,
    ADD = 0x04,
    MATMUL = 0x05,
    MKSCALAR = 0x06,
    SCALE = 0x07,
    SIGMOID = 0x08,
    SIGMOID_DERIV = 0x09,
    TRANSPOSE = 0x0A,
    COPY = 0x0B
};
#endif //ATHENA_OPCODES_H
