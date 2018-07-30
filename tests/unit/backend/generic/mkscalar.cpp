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

TEST( mkscalar_op_test, mkscalar_12_1_float ) {
    auto tensorShape = new TensorShape( { 1 } );
    auto tensor3 = new Tensor( *tensorShape, DataType::FLOAT );

    tensor3->setStartAddress( 1 );

    auto gmm = new GenericMemoryManager();
    gmm->setMemSize( 1000000 );
    gmm->init();

    gmm->addTensor( tensor3 );
    gmm->allocateAndLock( tensor3 );

    float a = 12.1;
    auto *ul = reinterpret_cast<unsigned long*>(&a);

    mkscalar(gmm, *ul, tensor3);

    float res[1];

    gmm->getData(1, 0, 4, res);
    ASSERT_FLOAT_EQ(*res, 12.1f);

    gmm->unlock( tensor3->getStartAddress());

    gmm->deinit();

}