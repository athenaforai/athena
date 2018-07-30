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

TEST( copy_op_test, copy_2x2 ) {
    auto tensorShape = new TensorShape( { 2, 2 } );
    auto tensor1 = new Tensor( *tensorShape, DataType::FLOAT );
    auto tensor3 = new Tensor( *tensorShape, DataType::FLOAT );

    tensor1->setStartAddress( 1 );
    tensor3->setStartAddress( 17 );

    auto gmm = new GenericMemoryManager();
    gmm->setMemSize( 1000000 );
    gmm->init();

    gmm->addTensor( tensor1 );
    gmm->allocateAndLock( tensor1 );

    float f[2][2];
    f[0][0] = 1.0f;
    f[0][1] = 2.0f;
    f[1][0] = 3.0f;
    f[1][1] = 4.0f;

    gmm->setData( 1, 0, 16, f );

    gmm->unlock( tensor1->getStartAddress());

    gmm->addTensor( tensor3 );
    gmm->allocateAndLock( tensor3 );
    gmm->loadAndLock( tensor1 );

    copy(gmm, tensor1, tensor3);

    float res[2][2];

    gmm->getData(17, 0, 16, res);
    ASSERT_FLOAT_EQ(res[0][0], 1.0f);
    ASSERT_FLOAT_EQ(res[0][1], 2.0f);
    ASSERT_FLOAT_EQ(res[1][0], 3.0f);
    ASSERT_FLOAT_EQ(res[1][1], 4.0f);

    gmm->getData(1, 0, 16, res);
    ASSERT_FLOAT_EQ(res[0][0], 1.0f);
    ASSERT_FLOAT_EQ(res[0][1], 2.0f);
    ASSERT_FLOAT_EQ(res[1][0], 3.0f);
    ASSERT_FLOAT_EQ(res[1][1], 4.0f);

    gmm->unlock( tensor1->getStartAddress());
    gmm->unlock( tensor3->getStartAddress());

    gmm->deinit();

}