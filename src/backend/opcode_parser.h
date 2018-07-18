//
// Created by Александр Баташев on 01.07.2018.
//

#ifndef ATHENA_OPCODE_PARSER_H
#define ATHENA_OPCODE_PARSER_H

#include <core/opcodes.h>
#include <vector>

namespace athena::backend {

    /**
     * Extract next command with its arguments from bytecode array (std::vector)
     * @param bytecode Vector with bytecode
     * @param next_word Start position to look through bytecode
     * @param new_word OpCode of the next word (Return value)
     * @param args Array of arguments (Return value) todo replace with vector
     * @param argc Number of args (Return value)
     * @return Position of next start value
     */
    unsigned int parse (
            std::vector< vm_word > &bytecode, unsigned int &next_word,
            OpCode &new_word, vm_word* args, unsigned int &argc
    );
}
#endif //ATHENA_OPCODE_PARSER_H
