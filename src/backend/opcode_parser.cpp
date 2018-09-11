/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaframework.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include <backend/opcodes.h>
#include <vector>
#include "opcode_parser.h"

namespace athena::backend {
    unsigned long parse (
            std::vector< vm_word > &bytecode, vm_word &next_word,
            vm_word &new_word, vm_word* args, unsigned long &argc,
            BasicOpCodeParams** parameters
    ) {

        *parameters = new BasicOpCodeParams;

        vm_word opcode = bytecode[ next_word ];
        vm_word params = opcode &
                         0b0000000000000000000000000000000011111111111111111111111111111111;
        opcode &= 0b1111111111111111111111111111111100000000000000000000000000000000;

        if ( opcode == OpCode::ADD ) {
            new_word = OpCode::ADD;
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::MATMUL ) {
            new_word = OpCode::MATMUL;
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
//            args[ 3 ] = bytecode[ ++next_word ];
//            args[ 4 ] = bytecode[ ++next_word ];
            auto mm = new MatMulParams;
            mm->transposeFirstArg =
                    static_cast<bool>(params & OpCodeParams::MATMUL_TRANSPOSE_FIRST);
            mm->transposeSecondArg =
                    static_cast<bool>(params & OpCodeParams::MATMUL_TRANSPOSE_SECOND);
            parameters = reinterpret_cast<BasicOpCodeParams**>(&mm);
        } else if ( opcode == OpCode::SIGMOID ) {
            new_word = OpCode::SIGMOID;
            argc = 2;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::TRANSPOSE ) {
            new_word = OpCode::TRANSPOSE;
            argc = 2;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::COPY ) {
            new_word = OpCode::COPY;
            argc = 2;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::MKSCALAR ) {
            new_word = OpCode::MKSCALAR;
            argc = 2;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::SCALE ) {
            new_word = OpCode::SCALE;
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::MSE ) {
            new_word = OpCode::MSE;
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::MSE_DERIV ) {
            new_word = OpCode::MSE_DERIV;
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::ALLOC ) {
            new_word = OpCode::ALLOC;
            argc = static_cast<unsigned int>(bytecode[ ++next_word ] + 1);

            for ( int i = 0; i < argc; i++ ) {
                args[ i ] = bytecode[ ++next_word ];
            }
        } else if ( opcode == OpCode::DEL ) {
            argc = 1;
            new_word = OpCode::DEL;
            args[ 0 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::MUL ) {
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
        } else if ( opcode == OpCode::HADAMARD ) {
            argc = 3;
            args[ 0 ] = bytecode[ ++next_word ];
            args[ 1 ] = bytecode[ ++next_word ];
            args[ 2 ] = bytecode[ ++next_word ];
        }

        ( *parameters )->resAddrMode = params & ( OpCodeParams::RES_ADDR_DIRECT |
                                                  OpCodeParams::RES_ADDR_BATCH );
        ( *parameters )->argAddrMode = params & ( OpCodeParams::ARG_ADDR_DIRECT |
                                                  OpCodeParams::ARG_ADDR_BATCH );

        return ++next_word;
    }
}