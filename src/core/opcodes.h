//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_OPCODES_H
#define ATHENA_OPCODES_H
enum class OpCode : uint32_t {
    DEL,
    PUSH,
    POP,
    JMP,
    ADD
};
#endif //ATHENA_OPCODES_H
