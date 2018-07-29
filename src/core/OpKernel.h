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

#ifndef ATHENA_OPKERNEL_H
#define ATHENA_OPKERNEL_H

#include <string>
#include <utility>
#include <vector>

#include "backend/opcodes.h"
#include <core/TensorShape.h>

namespace athena::core {
    /**
     * Operation skeleton
     * Each operation has OpCode
     */
    class OpKernel {
    protected:
        std::string name;
    public:
        explicit OpKernel ( std::string name ) : name( std::move( name )) {};

        /**
         * There can be unary, binary and other operations
         * @return Number of operands accepted
         */
        virtual int getOperandsCount () = 0;

        /**
         * It is important for some operations to have
         * certain size of their operands
         * @param shape Original operand shape
         * @param dim Dimensionality
         * @return New shape
         */
        virtual athena::core::TensorShape &getOutputShape (
                std::vector< athena::core::TensorShape > &shapes ) = 0;

        /**
         * It is important for some operations to have
         * certain size of their operands
         * @param shape Original operand shape
         * @param dim Dimensionality
         * @return New shape
         */
        virtual athena::core::TensorShape &getDerivativeShape (
                int d,
                std::vector< athena::core::TensorShape > &shapes ) = 0;

        virtual std::vector< vm_word >
        getOpBytecode ( std::vector< vm_word > args, vm_word resultCell ) = 0;

        /**
         * Generates bytecode to calculate partial derivative
         * @param d Number of variable with respect to which derivative is calculated
         * @param args Function arguments
         * @param resultCell Number of memory cell where results are saved
         * @return
         */
        virtual std::vector< vm_word > getDerivativeBytecode (
                int d, std::vector< vm_word > args,
                vm_word resultCell
        ) = 0;
    };
}


#endif //ATHENA_OPKERNEL_H
