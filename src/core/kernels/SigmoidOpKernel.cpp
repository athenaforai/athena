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

#include "SigmoidOpKernel.h"

athena::core::kernels::SigmoidOpKernel::SigmoidOpKernel ()
        : OpKernel( "sigmoid" ) {}

int athena::core::kernels::SigmoidOpKernel::getOperandsCount () {
    return 1;
}

std::vector< vm_word >
athena::core::kernels::SigmoidOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        vm_word resultCell
) {

    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::SIGMOID));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::SigmoidOpKernel::getDerivativeBytecode (
        int d,
        std::vector< vm_word > args,
        vm_word resultCell
) {

    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::SIGMOID_DERIV));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

athena::core::TensorShape &
athena::core::kernels::SigmoidOpKernel::getDerivativeShape (
        int d,
        std::vector< athena::core::TensorShape > &shapes ) {
    return shapes[ 0 ];
}

athena::core::TensorShape &athena::core::kernels::SigmoidOpKernel::getOutputShape (
        std::vector< athena::core::TensorShape > &shapes ) {
    return shapes[ 0 ];
}
