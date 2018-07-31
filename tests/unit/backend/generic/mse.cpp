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

TEST( mse_op_test, mse_7_2_vs_10_9 ) {
    auto tensorShape = new TensorShape( { 1 } );
    auto tensor1 = new Tensor( *tensorShape, DataType::FLOAT );
    auto tensor2 = new Tensor( *tensorShape, DataType::FLOAT );
    auto tensor3 = new Tensor( *tensorShape, DataType::FLOAT );

    tensor1->setStartAddress( 1 );
    tensor2->setStartAddress( 5 );
    tensor3->setStartAddress( 9 );

    auto gmm = new GenericMemoryManager();
    gmm->setMemSize( 1000000 );
    gmm->init();

    gmm->addTensor( tensor1 );
    gmm->allocateAndLock( tensor1 );
    float f1[] = { 7.2f };
    gmm->setData( 1, 0, 4, f1 );
    gmm->unlock( tensor1->getStartAddress());


    gmm->addTensor( tensor2 );
    gmm->allocateAndLock( tensor2 );
    float f2[] = { 10.9f };
    gmm->setData( 5, 0, 4, f2 );
    gmm->unlock( tensor2->getStartAddress());

    gmm->addTensor( tensor3 );
    gmm->allocateAndLock( tensor3 );

    gmm->loadAndLock( tensor1 );
    gmm->loadAndLock( tensor2 );
    mse( gmm, tensor1, tensor2, tensor3 );

    auto res = new float;

    gmm->getData( 9, 0, 4, res );

    gmm->unlock( tensor1->getStartAddress());
    gmm->unlock( tensor2->getStartAddress());
    gmm->unlock( tensor3->getStartAddress());

    ASSERT_FLOAT_EQ(*res, 13.69);

    gmm->deinit();
}