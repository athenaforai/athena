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

#include "MSELoss.h"

athena::core::loss::MSELoss::MSELoss () :
        AbstractLossFunction( new MSEOpKernel()) {};

athena::core::loss::MSEOpKernel::MSEOpKernel () :
        OpKernel( "mseloss" ) {}

int athena::core::loss::MSEOpKernel::getOperandsCount () {
    return 1;
}

std::vector< vm_word >
athena::core::loss::MSEOpKernel::getOpBytecode ( std::vector< vm_word > args,
                                                 vm_word resultCell ) {

    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::MSE));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

std::vector< vm_word >
athena::core::loss::MSEOpKernel::getDerivativeBytecode ( int d,
                                                         std::vector< vm_word > args,
                                                         vm_word resultCell ) {
    // todo depending on d the result needs to be scaled by -1
    std::vector< vm_word > bytecode;
    bytecode.push_back( static_cast<vm_word>(OpCode::MSE_DERIV));
    bytecode.push_back( args[ 0 ] );
    bytecode.push_back( args[ 1 ] );
    bytecode.push_back( resultCell );

    return bytecode;
}

athena::core::TensorShape &athena::core::loss::MSEOpKernel::getOutputShape (
        std::vector< athena::core::TensorShape > &shapes ) {
    auto s = new TensorShape( { 1 } );
    return *s;
}

athena::core::TensorShape &athena::core::loss::MSEOpKernel::getDerivativeShape ( int,
                                                                                 std::vector< athena::core::TensorShape > &shapes ) {
    return shapes[ 0 ];
}
