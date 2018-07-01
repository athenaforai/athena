//
// Created by Александр Баташев on 01.07.2018.
//

#ifndef ATHENA_OPCODE_PARSER_H
#define ATHENA_OPCODE_PARSER_H

#include <core/opcodes.h>
#include <vector>

namespace athena::backend {
    unsigned int parse(std::vector<vm_word> &bytecode, unsigned int next_word,
                       OpCode &new_word, vm_word* args, unsigned int &argc);
}
#endif //ATHENA_OPCODE_PARSER_H
