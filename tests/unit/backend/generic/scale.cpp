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

TEST( scale_op_test, scalef_test_2x2x2 ) {

//    auto tensorShape1 = new TensorShape( { 1 } );
//    auto tensorShape2 = new TensorShape( { 2, 2, 2 } );
//    auto tensor1 = new Tensor( *tensorShape1, DataType::FLOAT );
//    auto tensor2 = new Tensor( *tensorShape2, DataType::FLOAT );
//    auto tensor3 = new Tensor( *tensorShape2, DataType::FLOAT );
//
//    tensor1->setStartAddress( 1 );
//    tensor2->setStartAddress( 5 );
//    tensor3->setStartAddress( 37 );
//
//    auto gmm = new GenericMemoryManager();
//    gmm->setMemSize( 1000000 );
//    gmm->init();
//
//    gmm->addTensor( tensor1 );
//    gmm->allocateAndLock( tensor1 );
//
//    float f1[] = { 2.5f };
//    gmm->setData( 1, 0, 4, f1 );
//    gmm->unlock( tensor1->getStartAddress());
//
//    gmm->addTensor( tensor2 );
//    gmm->allocateAndLock( tensor2 );
//
//    float f2[2][2][2];
//    f2[0][0][0] = 1.0f;
//    f2[0][0][1] = 2.0f;
//    f2[0][1][0] = 3.0f;
//    f2[0][1][1] = 4.0f;
//    f2[1][0][0] = 5.0f;
//    f2[1][0][1] = 6.0f;
//    f2[1][1][0] = 7.0f;
//    f2[1][1][1] = 8.0f;
//    gmm->setData( 5, 0, 32, f2 );
//    gmm->unlock( tensor2->getStartAddress());
//
//    gmm->addTensor( tensor3 );
//    gmm->allocateAndLock( tensor3 );
//    gmm->loadAndLock( tensor1 );
//    gmm->loadAndLock( tensor2 );
//
//    scale( gmm, tensor1, tensor2, tensor3 );
//
//    float res[2][2][2];
//    gmm->getData( 37, 0, 32, res );
//
//    gmm->unlock( tensor1->getStartAddress());
//    gmm->unlock( tensor2->getStartAddress());
//    gmm->unlock( tensor3->getStartAddress());
//
//    ASSERT_FLOAT_EQ(res[0][0][0], 2.5f);
//    ASSERT_FLOAT_EQ(res[0][0][1], 5.0f);
//    ASSERT_FLOAT_EQ(res[0][1][0], 7.5f);
//    ASSERT_FLOAT_EQ(res[0][1][1], 10.0f);
//    ASSERT_FLOAT_EQ(res[1][0][0], 12.5f);
//    ASSERT_FLOAT_EQ(res[1][0][1], 15.0f);
//    ASSERT_FLOAT_EQ(res[1][1][0], 17.5f);
//    ASSERT_FLOAT_EQ(res[1][1][1], 20.0f);
//
//    gmm->deinit();
//
//    delete gmm;
}

TEST( scale_op_test, scalef_test_2x2 ) {    //TODO NOW FAULT

//    auto tensorShape1 = new TensorShape( { 1 } );
//    auto tensorShape2 = new TensorShape( { 2, 2} );
//    auto tensor1 = new Tensor( *tensorShape1, DataType::FLOAT );
//    auto tensor2 = new Tensor( *tensorShape2, DataType::FLOAT );
//    auto tensor3 = new Tensor( *tensorShape2, DataType::FLOAT );
//
//    tensor1->setStartAddress( 1 );
//    tensor2->setStartAddress( 5 );
//    tensor3->setStartAddress( 21 );
//
//    auto gmm = new GenericMemoryManager();
//    gmm->setMemSize( 1000000 );
//    gmm->init();
//
//    gmm->addTensor( tensor1 );
//    gmm->allocateAndLock( tensor1 );
//
//    float f1[] = { 2.5f };
//    gmm->setData( 1, 0, 4, f1 );
//    gmm->unlock( tensor1->getStartAddress());
//
//    gmm->addTensor( tensor2 );
//    gmm->allocateAndLock( tensor2 );
//
//    float f2[2][2];
//    f2[0][0] = 1.0f;
//    f2[0][1] = 2.0f;
//    f2[1][0] = 3.0f;
//    f2[1][1] = 4.0f;
//    gmm->setData( 5, 0, 16, f2 );
//    gmm->unlock( tensor2->getStartAddress());
//
//    gmm->addTensor( tensor3 );
//    gmm->allocateAndLock( tensor3 );
//    gmm->loadAndLock( tensor1 );
//    gmm->loadAndLock( tensor2 );
//
//    scale( gmm, tensor1, tensor2, tensor3 );
//
//    float res[2][2];
//    gmm->getData( 21, 0, 16, res );
//
//    gmm->unlock( tensor1->getStartAddress());
//    gmm->unlock( tensor2->getStartAddress());
//    gmm->unlock( tensor3->getStartAddress());
//
//    ASSERT_FLOAT_EQ(res[0][0], 2.5f);
//    ASSERT_FLOAT_EQ(res[0][1], 5.0f);
//    ASSERT_FLOAT_EQ(res[1][0], 7.5f);
//    ASSERT_FLOAT_EQ(res[1][1], 10.0f);
//
//    gmm->deinit();
//
//    delete gmm;
}


TEST( scale_op_test, scalef_test_1x1 ) {

//    auto tensorShape1 = new TensorShape( { 1 } );
//    auto tensor1 = new Tensor( *tensorShape1, DataType::FLOAT );
//    auto tensor2 = new Tensor( *tensorShape1, DataType::FLOAT );
//    auto tensor3 = new Tensor( *tensorShape1, DataType::FLOAT );
//
//    tensor1->setStartAddress( 1 );
//    tensor2->setStartAddress( 5 );
//    tensor3->setStartAddress( 9 );
//
//    auto gmm = new GenericMemoryManager();
//    gmm->setMemSize( 1000000 );
//    gmm->init();
//
//    gmm->addTensor( tensor1 );
//    gmm->allocateAndLock( tensor1 );
//
//    float f1[] = { 2.5f };
//    gmm->setData( 1, 0, 4, f1 );
//    gmm->unlock( tensor1->getStartAddress());
//
//    gmm->addTensor( tensor2 );
//    gmm->allocateAndLock( tensor2 );
//
//    float f2[1];
//    f2[0] = 4.0f;
//    gmm->setData( 5, 0, 4, f2 );
//    gmm->unlock( tensor2->getStartAddress());
//
//    gmm->addTensor( tensor3 );
//    gmm->allocateAndLock( tensor3 );
//    gmm->loadAndLock( tensor1 );
//    gmm->loadAndLock( tensor2 );
//
//    scale( gmm, tensor1, tensor2, tensor3 );
//
//    float res[1];
//    gmm->getData( 9, 0, 4, res );
//
//    gmm->unlock( tensor1->getStartAddress());
//    gmm->unlock( tensor2->getStartAddress());
//    gmm->unlock( tensor3->getStartAddress());
//
//    ASSERT_FLOAT_EQ(res[0], 10.0f);
//
//    gmm->deinit();
//
//    delete gmm;
}