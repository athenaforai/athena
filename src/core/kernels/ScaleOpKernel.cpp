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

#include "ScaleOpKernel.h"

int athena::core::kernels::ScaleOpKernel::getOperandsCount () {
    return 2;
}

std::vector< vm_word >
athena::core::kernels::ScaleOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        vm_word resultCell ) {
    std::vector< vm_word > bytecode;

    bytecode.push_back( OpCode::SCALE);
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::ScaleOpKernel::getDerivativeBytecode ( int d,
                                                              std::vector< vm_word > args,
                                                              vm_word resultCell ) {
    std::vector< vm_word > bytecode;

    //?? CodeOp and Args todo

    bytecode.push_back( resultCell );

    return std::vector< vm_word >();
}

athena::core::TensorShape &athena::core::kernels::ScaleOpKernel::getOutputShape (
        std::vector< athena::core::TensorShape > &shapes ) {
    return shapes[ 1 ];
}

athena::core::TensorShape &
athena::core::kernels::ScaleOpKernel::getDerivativeShape (
        int d,
        std::vector< athena::core::TensorShape > &shapes ) {
    return shapes[ d ];
}
