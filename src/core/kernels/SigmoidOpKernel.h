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

#ifndef ATHENA_SIGMOIDOPKERNEL_H
#define ATHENA_SIGMOIDOPKERNEL_H


#include <core/OpKernel.h>

namespace athena::core::kernels {

    /**
     * Apply sigmoid function to every element of Tensor.
     * See https://en.wikipedia.org/wiki/Sigmoid_function for more info
     */
    class SigmoidOpKernel : public OpKernel {
    public:
        SigmoidOpKernel ();

        int getOperandsCount () override;

        athena::core::TensorShape &getOutputShape (
                std::vector< athena::core::TensorShape > &shapes ) override;

        athena::core::TensorShape &
        getDerivativeShape ( int d,
                             std::vector< athena::core::TensorShape > &shapes ) override;

        std::vector< vm_word >
        getOpBytecode ( std::vector< vm_word > args, vm_word resultCell ) override;

        std::vector< vm_word > getDerivativeBytecode (
                int d, std::vector< vm_word > args,
                vm_word resultCell
        ) override;

    };

}


#endif //ATHENA_SIGMOIDOPKERNEL_H
