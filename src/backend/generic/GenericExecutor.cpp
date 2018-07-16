//
// Created by Александр Баташев on 26.05.2018.
//

#include "GenericExecutor.h"
#include <core/opcodes.h>
#include <stdexcept>
#include <backend/opcode_parser.h>
#include "ops.h"

using namespace athena::core;

void athena::backend::generic::GenericExecutor::execute () {
    unsigned int ip = 0;
    OpCode op;
    auto args = new vm_word[10];
    unsigned int argc = 0;

    auto gmm = dynamic_cast<GenericMemoryManager*>(device->getMemoryManager());

    while ( parse( bytecode, ip, op, args, argc ) < bytecode.size()) {
        switch ( op ) {
            case OpCode::ADD: {
//                Tensor* a = memory[ args[ 0 ]];
//                Tensor* b = memory[ args[ 1 ]];
                /*memory[ args[ 2 ]] =*/
                gmm->load( args[ 0 ] );
                gmm->load( args[ 1 ] );
                gmm->load( args[ 2 ] );
                add( gmm,
                     gmm->getTensor( args[ 0 ] ),
                     gmm->getTensor( args[ 1 ] ),
                     gmm->getTensor( args[ 2 ] ));

                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 2 ] );
                break;
            }
            case OpCode::MATMUL: {

                gmm->load( args[ 1 ] );
                gmm->load( args[ 3 ] );
                gmm->load( args[ 4 ] );

                auto aTransp = static_cast<bool>(args[ 0 ]);
                Tensor* a = gmm->getTensor( args[ 1 ] );
                auto bTransp = static_cast<bool>( args[ 2 ]);
                Tensor* b = gmm->getTensor( args[ 3 ] );
                Tensor* res = gmm->getTensor( args[ 4 ] );
                matmul( gmm, aTransp, a, bTransp, b, res );

                gmm->unlock( args[ 1 ] );
                gmm->unlock( args[ 3 ] );
                gmm->unlock( args[ 4 ] );
            }
            case OpCode::SIGMOID: {
                gmm->load( args[ 0 ] );
                gmm->load( args[ 1 ] );
                Tensor* x = gmm->getTensor( args[ 0 ]);
                memory[ args[ 1 ]] = sigmoid( x );
                gmm->unlock( args[ 0 ] );
                gmm->unlock( args[ 1 ] );
            }
            case OpCode::SIGMOID_DERIV: {
                Tensor* x = memory[ args[ 0 ]];
                memory[ args[ 1 ]] = sigmoid_deriv( x );
            }
            case OpCode::SCALE: {
                Tensor* x = memory[ args[ 0 ]];
                Tensor* y = memory[ args[ 1 ]];
                memory[ args[ 2 ]] = scale( x, y );
            }
            case OpCode::MSE: {
                Tensor* x = memory[ args[ 0 ]];
                Tensor* y = memory[ args[ 1 ]];
                memory[ args[ 2 ]] = mse( x, y );
            }
            case OpCode::MSE_DERIV: {
                Tensor* x = memory[ args[ 0 ]];
                Tensor* y = memory[ args[ 1 ]];
                memory[ args[ 2 ]] = mse( x, y );
            }
            case OpCode::MKSCALAR: {
                unsigned long x = args[ 0 ];
                memory[ args[ 1 ]] = mkscalar( x );
            }
            default:
                throw std::runtime_error( "Unknown instruction" );
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

athena::backend::AbstractMemoryManager*
athena::backend::generic::GenericExecutor::getMemoryManager () {
    return device->getMemoryManager();
}