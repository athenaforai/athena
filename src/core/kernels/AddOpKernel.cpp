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

#include <algorithm>
#include <vector>
#include "AddOpKernel.h"

int athena::core::kernels::AddOpKernel::getOperandsCount () {
    return 2;
}


std::vector< vm_word > athena::core::kernels::AddOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        vm_word resultCell ) {
    std::vector< vm_word > bytecode;

    bytecode.push_back( OpCode::ADD);

    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );

    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::AddOpKernel::getDerivativeBytecode (
        int d,
        std::vector< vm_word > args,
        vm_word resultCell ) {
    std::vector< vm_word > bytecode;
    bytecode.push_back( OpCode::MKSCALAR);

    float unit = 1;
    auto u = reinterpret_cast<vm_word*>(&unit);

    bytecode.push_back( *u );
    bytecode.push_back( resultCell );

    return bytecode;

}

athena::core::TensorShape &athena::core::kernels::AddOpKernel::getOutputShape (
        std::vector< athena::core::TensorShape > &shapes ) {
    return shapes[ 0 ];
}

athena::core::TensorShape &athena::core::kernels::AddOpKernel::getDerivativeShape (
        int d,
        std::vector< athena::core::TensorShape > &shapes
) {

    return shapes[d];

}
