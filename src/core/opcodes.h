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

#ifndef ATHENA_OPCODES_H
#define ATHENA_OPCODES_H

typedef unsigned long vm_word;

enum class OpCode : vm_word {
    DEL = 0x00,
    PUSH = 0x01,
    POP = 0x02,
    JMP = 0x03,
    ADD = 0x04,
    MATMUL = 0x05,
    MKSCALAR = 0x06,
    SCALE = 0x07,
    SIGMOID = 0x08,
    SIGMOID_DERIV = 0x09,
    TRANSPOSE = 0x0A,
    COPY = 0x0B,
    MSE = 0x0C,
    MSE_DERIV = 0x0D,
    ALLOC = 0x0E,
    MUL = 0x0F,
    HADAMARD = 0x10
};
#endif //ATHENA_OPCODES_H
