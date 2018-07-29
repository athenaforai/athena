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

#include <gtest/gtest.h>
#include <core/Tensor.h>
#include <backend/generic/ops.h>

using namespace athena::core;
using namespace athena::backend::generic;

TEST( matmul_op_test, matmul_unit ){
//    TensorShape shape ( { 3, 3 } );
//
//    float data1[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
//    float data2[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
//
//    Tensor a ( shape, DataType::FLOAT, reinterpret_cast<unsigned char*>( data1 ));
//    Tensor b ( shape, DataType::FLOAT, reinterpret_cast<unsigned char*>( data2 ));
//
//    auto res = matmul ( false, &a, false, &b );
//
//    auto resData = reinterpret_cast<float*>(res->raw ());
//
//    for ( int i = 0; i < 9; i++ ) {
//        ASSERT_FLOAT_EQ ( data1[ i ], resData[ i ] );
//    }


}

