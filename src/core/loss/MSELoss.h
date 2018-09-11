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

#ifndef ATHENA_MSELOSS_H
#define ATHENA_MSELOSS_H

#include <core/InputNode.h>
#include "AbstractLossFunction.h"

namespace athena::core::loss {

    class MSEOpKernel : public OpKernel {
    public:
        MSEOpKernel ();

        int getOperandsCount () override ;

        athena::core::TensorShape &getOutputShape (
                std::vector< athena::core::TensorShape > &shapes ) override;

        athena::core::TensorShape &getDerivativeShape (
                int,
                std::vector< athena::core::TensorShape > &shapes ) override ;

        std::vector< vm_word >
        getOpBytecode (
                std::vector< vm_word > args,
                vm_word resultCell
        ) override ;

        std::vector< vm_word > getDerivativeBytecode (
                int d, std::vector< vm_word > args,
                vm_word resultCell
        ) override ;
    };

    class MSELoss : public AbstractLossFunction {
    public:
        explicit MSELoss ();

    };

}


#endif //ATHENA_MSELOSS_H
