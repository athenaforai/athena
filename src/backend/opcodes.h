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

#pragma once
#ifndef ATHENA_OPCODES_H
#define ATHENA_OPCODES_H

#include <vector>

typedef unsigned long vm_word;

/**
 * \file opcodes.h
 * <p>OpCode specifies digital codes for Athena VM's operations. Operation is
 * encoded with operation code and its parameters. Bits 0..31 (assuming little-endian)
 * are used by operation code. Bits 32..63 are used by operation parameters.</p>
 * <p>
 * <h6>Description of Athena VM operations</h6>
 * <table>
 * <tr>
 *  <th>Operation</th>
 *  <th>Description</th>
 *  <th>Parameters</th>
 *  <th>Arguments</th>
 * </tr>
 * <tr>
 *  <td>ADD</td>
 *  <td>Produces sum of two Tensors</td>
 *  <td></td>
 *  <td>3 arguments: pointers to two summands and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>MATMUL</td>
 *  <td>Produces product of two matrix Tensors</td>
 *  <td>todo describe 2 parameters: transpose args</td>
 *  <td>3 arguments: pointers to two matrices and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>MKSCALAR</td>
 *  <td>Creates Tensor from scalar constant</td>
 *  <td>todo describe 1 parameter: data type</td>
 *  <td>2 arguments: scalar and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>SCALE</td>
 *  <td>Multiplies every Tensor element by scalar</td>
 *  <td>No parameters</td>
 *  <td>3 arguments: pointers to scalar Tensor, source Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>SIGMOID</td>
 *  <td>Applies sigmoid function to every element of Tensor</td>
 *  <td>No parameters</td>
 *  <td>2 arguments: source Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>SIGMOID_DERIV</td>
 *  <td>Calculates derivative of sigmoid function</td>
 *  <td>No parameters</td>
 *  <td>2 arguments: source Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>TRANSPOSE</td>
 *  <td>Transpose matrix Tensor</td>
 *  <td>No parameters</td>
 *  <td>2 arguments: source Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>TRANSPOSE</td>
 *  <td>Transpose matrix Tensor</td>
 *  <td>No parameters</td>
 *  <td>2 arguments: source Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>COPY</td>
 *  <td>Copy Tensor</td>
 *  <td>No parameters</td>
 *  <td>2 arguments: source Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>MSE</td>
 *  <td>Calculate minimal squared error</td>
 *  <td>No parameters</td>
 *  <td>3 arguments: produced Tensor, label Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>MSE_DERIV</td>
 *  <td>Calculate derivative of minimal squared error</td>
 *  <td>No parameters</td>
 *  <td>3 arguments: produced Tensor, label Tensor and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>ALLOC</td>
 *  <td>Allocate memory for Tensor</td>
 *  <td>todo describe one parameter: data type</td>
 *  <td>First argument always specifies number of dimensions, last arg
 *  specifies virtual address of new Tensor.</td>
 * </tr>
 * <tr>
 *  <td>MUL</td>
 *  <td>Multiply two Tensors</td>
 *  <td>No parameters</td>
 *  <td>3 arguments: multiplier Tensors and result Tensor</td>
 * </tr>
 * <tr>
 *  <td>HADAMARD</td>
 *  <td>Do element-wise multiplication of two matrices</td>
 *  <td>No parameters</td>
 *  <td>3 arguments: multiplier Tensors and result Tensor</td>
 * </tr>
 * </table>
 */
class OpCode {
public:
    static const vm_word DEL;
    static const vm_word PUSH;
    static const vm_word POP;
    static const vm_word JMP;
    static const vm_word ADD;
    static const vm_word MATMUL;
    static const vm_word MKSCALAR;
    static const vm_word SCALE;
    static const vm_word SIGMOID;
    static const vm_word SIGMOID_DERIV;
    static const vm_word TRANSPOSE;
    static const vm_word COPY;
    static const vm_word MSE;
    static const vm_word MSE_DERIV;
    static const vm_word ALLOC;
    static const vm_word MUL;
    static const vm_word HADAMARD;
};

class OpCodeParams {
public:
    // Common parameters
    // Result value addressing modes
    /**
     * Access result Tensor directly by virtual address
     */
    static const vm_word RES_ADDR_DIRECT = 0b00000000000000000000000000000000;
    /**
     * Get virtual address of Subtensor with respect to current batch number
     */
    static const vm_word RES_ADDR_BATCH = 0b00000000000000000000000000000001;

    // Arguments values addressing modes
    /**
     * Access result Tensor directly by virtual address
     */
    static const vm_word ARG_ADDR_DIRECT = 0b00000000000000000000000000000000;
    /**
     * Get virtual address of Subtensor with respect to current batch number
     */
    static const vm_word ARG_ADDR_BATCH = 0b00000000000000000000000000001000;

    // MKSCALAR parameters
    static const vm_word MKSCALAR_FLOAT = 0b00000000000000000000000000000000;
    static const vm_word MKSCALAR_DOUBLE = 0b00000000000000000000000001000000;
    static const vm_word MKSCALAR_HALF = 0b00000000000000000000000010000000;
};

struct BasicOpCodeParams {
    vm_word resAddrMode = OpCodeParams::RES_ADDR_DIRECT;
    vm_word argAddrMode = OpCodeParams::ARG_ADDR_DIRECT;
};

vm_word buildOpCode ( vm_word opCode, std::vector< vm_word > parameters );

#endif //ATHENA_OPCODES_H
