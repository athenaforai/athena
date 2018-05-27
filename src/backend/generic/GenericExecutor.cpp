//
// Created by Александр Баташев on 26.05.2018.
//

#include "GenericExecutor.h"
#include <core/opcodes.h>
#include <stdexcept>
#include "ops.h"

using namespace athena::core;

void athena::backend::generic::GenericExecutor::execute() {
    unsigned int ip = 0;

    while (ip < bytecode.size()) {
        int opcode = bytecode[ip];

        switch (opcode) {
            case static_cast<int>(OpCode::DEL): {
                memory[bytecode[++ip]] = nullptr;
                break;
            }
            case static_cast<int>(OpCode::PUSH): {
                ++ip;
                // todo implement push, pop, jmp
                break;
            }
            case static_cast<int>(OpCode::POP): {
                ++ip;
                // todo implement push, pop, jmp
                break;
            }
            case static_cast<int>(OpCode::JMP): {
                ++ip;
                // todo implement push, pop, jmp
                break;
            }
            case static_cast<int>(OpCode::ADD): {
                Tensor *a = memory[bytecode[++ip]];
                Tensor *b = memory[bytecode[++ip]];
                memory[bytecode[++ip]] = add(a, b);
                break;
            }
            default:
                throw std::runtime_error("Unknown instruction");
        }

        ip++;
    }

}

void athena::backend::generic::GenericExecutor::setMemoryCell(unsigned long id, athena::core::Tensor *tensor) {

    memory[id] = tensor;
}

athena::core::Tensor *athena::backend::generic::GenericExecutor::getMemoryCell(unsigned long id) {
    return memory[id];
}
