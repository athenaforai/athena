//
// Created by Александр Баташев on 01.07.2018.
//

#include <core/opcodes.h>
#include <vector>
#include "opcode_parser.h"

namespace athena::backend {
    unsigned int parse (
            std::vector< vm_word > &bytecode, unsigned int next_word,
            OpCode &new_word, vm_word* args, unsigned int &argc
    ) {

        vm_word opcode = bytecode[ next_word ];

        switch ( opcode ) {
            case static_cast<vm_word>(OpCode::ADD): {
                new_word = OpCode::ADD;
                argc = 3;
                args[ 0 ] = bytecode[ ++next_word ];
                args[ 1 ] = bytecode[ ++next_word ];
                args[ 2 ] = bytecode[ ++next_word ];
                break;
            }
            case static_cast<vm_word>(OpCode::MATMUL): {
                new_word = OpCode::MATMUL;
                argc = 5;
                args[ 0 ] = bytecode[ ++next_word ];
                args[ 1 ] = bytecode[ ++next_word ];
                args[ 2 ] = bytecode[ ++next_word ];
                args[ 3 ] = bytecode[ ++next_word ];
                args[ 4 ] = bytecode[ ++next_word ];
                break;
            }
            case static_cast<vm_word>(OpCode::SIGMOID): {
                new_word = OpCode::SIGMOID;
                argc = 2;
                args[ 0 ] = bytecode[ ++next_word ];
                args[ 1 ] = bytecode[ ++next_word ];
            }
            case static_cast<vm_word>(OpCode::TRANSPOSE): {
                new_word = OpCode::TRANSPOSE;
                argc = 2;
                args[ 0 ] = bytecode[ ++next_word ];
                args[ 1 ] = bytecode[ ++next_word ];
            }
            case static_cast<vm_word>(OpCode::COPY): {
                new_word = OpCode::COPY;
                argc = 2;
                args[ 0 ] = bytecode[ ++next_word ];
                args[ 1 ] = bytecode[ ++next_word ];
            }
            default:
                break;
        }


        return ++next_word;
    }
}