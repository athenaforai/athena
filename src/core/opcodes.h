//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_OPCODES_H
#define ATHENA_OPCODES_H
enum class OpCode : int {
    DEL = 0x00,
    PUSH = 0x01,
    POP = 0x02,
    JMP = 0x03,
    ADD = 0x04
};
#endif //ATHENA_OPCODES_H
