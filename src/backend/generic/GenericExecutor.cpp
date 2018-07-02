//
// Created by Александр Баташев on 26.05.2018.
//

#include "GenericExecutor.h"
#include <core/opcodes.h>
#include <stdexcept>
#include <backend/opcode_parser.h>
#include "ops.h"

using namespace athena::core;

void athena::backend::generic::GenericExecutor::execute (){
    unsigned int ip = 0;
    OpCode op;
    auto args = new vm_word[10];
    unsigned int argc = 0;

    while ( parse ( bytecode, ip, op, args, argc )) {
        switch ( op ) {
            case OpCode::ADD: {
                Tensor* a = memory[ args[ 0 ]];
                Tensor* b = memory[ args[ 1 ]];
                memory[ args[ 2 ]] = add ( a, b );
                break;
            }
            case OpCode::MATMUL: {
                auto aTransp = static_cast<bool>(memory[ args[ 0 ]]);
                Tensor* a = memory[ args[ 1 ]];
                auto bTransp = static_cast<bool>(memory[ args[ 2 ]]);
                Tensor* b = memory[ args[ 3 ]];
                memory[ args[ 4 ]] = matmul ( aTransp, a, bTransp, b );
            }
            case OpCode::SIGMOID: {
                Tensor* x = memory[ args[ 0 ]];
                memory[ args[ 1 ]] = sigmoid ( x );
            }
            case OpCode::SIGMOID_DERIV: {
                Tensor* x = memory[ args[ 0 ]];
                memory[ args[ 1 ]] = sigmoid_deriv ( x );
            }
            default:
                throw std::runtime_error ( "Unknown instruction" );
        }
    }

//    while (ip < bytecode.size()) {
//        int opcode = bytecode[ip];
//
//        switch (opcode) {
//            case static_cast<int>(OpCode::DEL): {
//                memory[bytecode[++ip]] = nullptr;
//                break;
//            }
//            case static_cast<int>(OpCode::PUSH): {
//                ++ip;
//                // todo implement push, pop, jmp
//                break;
//            }
//            case static_cast<int>(OpCode::POP): {
//                ++ip;
//                // todo implement push, pop, jmp
//                break;
//            }
//            case static_cast<int>(OpCode::JMP): {
//                ++ip;
//                // todo implement push, pop, jmp
//                break;
//            }
//            case static_cast<int>(OpCode::ADD): {
//                Tensor *a = memory[bytecode[++ip]];
//                Tensor *b = memory[bytecode[++ip]];
//                memory[bytecode[++ip]] = add(a, b);
//                break;
//            }
//            default:
//                throw std::runtime_error("Unknown instruction");
//        }
//
//        ip++;
//    }

}

void athena::backend::generic::GenericExecutor::setMemoryCell (
        unsigned long id, athena::core::Tensor* tensor
){

    memory[ id ] = tensor;
}

athena::core::Tensor*
athena::backend::generic::GenericExecutor::getMemoryCell ( unsigned long id ){
    return memory[ id ];
}
