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

#include <backend/generic/GenericMemoryManager.h>
#include <gtest/gtest.h>
#include <core/Tensor.h>

using namespace athena::backend::generic;
using namespace athena::core;

TEST( generic_memory_manager_tests, add_get_Test ) {

    auto tensorShape = new TensorShape( { 3, 2 } );
    auto tensor = new Tensor( *tensorShape, DataType::FLOAT );

    tensor->setStartAddress( 1 );

    auto gmm = new GenericMemoryManager();

    gmm->addTensor( tensor );

    auto t2 = gmm->getTensor( tensor->getStartAddress());

    ASSERT_EQ( tensor, t2 );

}

TEST( generic_memory_manager_tests, physical_addres_Test ) {

    auto tensorShape = new TensorShape( { 3 } );
    auto tensor = new Tensor( *tensorShape, DataType::FLOAT );

    tensor->setStartAddress( 1 );

    auto gmm = new GenericMemoryManager();
    gmm->setMemSize( 1000000 );
    gmm->init();

    gmm->addTensor( tensor );
    gmm->allocateAndLock( tensor );

    float f[] = { 2, 3, 4 };

    gmm->setData( 1, 0, 12, f );

//    gmm->unlock( tensor->getStartAddress());

    auto rf =
            reinterpret_cast<float*>(gmm->getPhysicalAddress( tensor->getStartAddress()));

//    gmm->loadAndLock( tensor );
//    gmm->getData( 1, 0, 12, rf );
    gmm->unlock( tensor->getStartAddress());

    for ( int i = 0; i < 3; i++ ) {
        EXPECT_FLOAT_EQ( f[ i ], rf[ i ] );
    }

    gmm->deinit();
}

TEST( generic_memory_manager_tests, set_get_data_Test ) {

    auto tensorShape = new TensorShape( { 3 } );
    auto tensor = new Tensor( *tensorShape, DataType::FLOAT );

    tensor->setStartAddress( 1 );

    auto gmm = new GenericMemoryManager();
    gmm->setMemSize( 1000000 );
    gmm->init();

    gmm->addTensor( tensor );
    gmm->allocateAndLock( tensor );

    float f[] = { 2, 3, 4 };

    gmm->setData( 1, 0, 12, f );

    gmm->unlock( tensor->getStartAddress());

    auto rf = new float[3];

    gmm->loadAndLock( tensor );
    gmm->getData( 1, 0, 12, rf );
    gmm->unlock( tensor->getStartAddress());

    for ( int i = 0; i < 3; i++ ) {
        EXPECT_FLOAT_EQ( f[ i ], rf[ i ] );
    }

    gmm->deinit();
}