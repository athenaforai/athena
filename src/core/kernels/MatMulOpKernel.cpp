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

#include "MatMulOpKernel.h"

int athena::core::kernels::MatMulOpKernel::getOperandsCount () {
    return 2;
}

std::vector< vm_word >
athena::core::kernels::MatMulOpKernel::getOpBytecode (
        std::vector< vm_word > args,
        vm_word resultCell ) {

    std::vector< vm_word > bytecode;

    bytecode.push_back( OpCode::MATMUL);
    bytecode.push_back( 0 );
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( 0 );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::kernels::MatMulOpKernel::getDerivativeBytecode ( int d,
                                                               std::vector< vm_word > args,
                                                               vm_word resultCell ) {

    std::vector< vm_word > bytecode;

    if ( d == 0 ) {
        bytecode.push_back( OpCode::COPY);
        bytecode.push_back( args[ 0 ] );
    } else {
        bytecode.push_back( OpCode::TRANSPOSE);
        bytecode.push_back( args[ 1 ] );
    }
    bytecode.push_back( resultCell );

    return std::vector< vm_word >();
}

athena::core::TensorShape &athena::core::kernels::MatMulOpKernel::getOutputShape (
        std::vector< athena::core::TensorShape > &shapes ) {
    auto shape = new TensorShape( { shapes[ 0 ].dim( 0 ), shapes[ 1 ].dim( 1 ) } );
    return *shape;
}

athena::core::TensorShape &
athena::core::kernels::MatMulOpKernel::getDerivativeShape (
        int d,
        std::vector< athena::core::TensorShape > &shapes ) {
    if ( d == 0 ) {
        return shapes[ 0 ];
    } else {
        auto s = new TensorShape( { shapes[ 1 ].dim( 1 ), shapes[ 1 ].dim( 0 ) } );
        return *s;
    }
}


