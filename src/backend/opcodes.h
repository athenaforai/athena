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

/**
 * \enum OpCode
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
enum class OpCode : vm_word {
    DEL = 0x0000000000,
    PUSH = 0x0100000000,
    POP = 0x0200000000,
    JMP = 0x0300000000,
    ADD = 0x0400000000,
    MATMUL = 0x0500000000,
    MKSCALAR = 0x0600000000,
    SCALE = 0x0700000000,
    SIGMOID = 0x0800000000,
    SIGMOID_DERIV = 0x0900000000,
    TRANSPOSE = 0x0A00000000,
    COPY = 0x0B00000000,
    MSE = 0x0C00000000,
    MSE_DERIV = 0x0D00000000,
    ALLOC = 0x0E00000000,
    MUL = 0x0F00000000,
    HADAMARD = 0x1000000000
};

struct BasicOpCodeParams{

};
#endif //ATHENA_OPCODES_H
