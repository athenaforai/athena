/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaproject.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT 
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the 
 * License for the specific language governing permissions and limitations under
 * the License.
 */
#include "opcodes.h"

const vm_word OpCode::DEL = 0x0000000000UL;
const vm_word OpCode::PUSH = 0x0100000000;
const vm_word OpCode::POP = 0x0200000000;
const vm_word OpCode::JMP = 0x0300000000;
const vm_word OpCode::ADD = 0x0400000000;
const vm_word OpCode::MATMUL = 0x0500000000;
const vm_word OpCode::MKSCALAR = 0x0600000000;
const vm_word OpCode::SCALE = 0x0700000000;
const vm_word OpCode::SIGMOID = 0x0800000000;
const vm_word OpCode::SIGMOID_DERIV = 0x0900000000;
const vm_word OpCode::TRANSPOSE = 0x0A00000000;
const vm_word OpCode::COPY = 0x0B00000000;
const vm_word OpCode::MSE = 0x0C00000000;
const vm_word OpCode::MSE_DERIV = 0x0D00000000;
const vm_word OpCode::ALLOC = 0x0E00000000;
const vm_word OpCode::MUL = 0x0F00000000;
const vm_word OpCode::HADAMARD = 0x100000000;

vm_word buildOpCode ( vm_word opCode, std::vector< vm_word > parameters ) {
    vm_word res = opCode;
    for ( vm_word param : parameters ) {
        res |= param;
    }
    return res;
}