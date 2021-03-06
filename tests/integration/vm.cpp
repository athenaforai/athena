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
#include <core/Session.h>
#include <core/Tensor.h>
#include <core/InputNode.h>
#include <ops/ops.h>
#include <core/loss/MSELoss.h>
#include <core/optimizers/GradientDescent.h>
#include <backend/generic/CPUDevice.h>
#include <backend/generic/GenericExecutor.h>
#include <core/initializers/DataInitializer.h>
#include <core/optimizers/GradientDescent.h>

using namespace athena::core;
using namespace athena::core::loss;
using namespace athena::core::optimizers;
using namespace athena::core::initializers;

using namespace athena::backend::generic;

TEST( vm_test, vm_test_simple_Test ) {
    Session sess;

    auto device = new CPUDevice();

    GenericExecutor executor(device);

    sess.setExecutor( &executor );

    TensorShape shape( { 3 } );

    auto a = new Tensor( shape, DataType::FLOAT );
    auto b = new Tensor( shape, DataType::FLOAT );

    float fa[] = {1, 2, 3};
    float fb[] = {2, 3, 4};

    auto ain = new InputNode( a );
    auto aInitializer = new DataInitializer();
    aInitializer->setData( reinterpret_cast<void*>(fa), sizeof( float ) * 3 );
    ain->setInitializer( aInitializer );

    auto bin = new InputNode( b );
    auto bInitializer = new DataInitializer();
    bInitializer->setData( reinterpret_cast<void*>(fb), sizeof( float ) * 3 );
    bin->setInitializer( bInitializer );

    auto logits = athena::ops::add( ain, bin );

    sess.prepare( logits );

    // todo Костыль. Нужен нормальный интерфейс
    device->getMemoryManager()->addTensor( a );
    device->getMemoryManager()->addTensor( b );

    auto resTensor = sess.run();

    auto resf = new float[3];

    device->getMemoryManager()->loadAndLock( resTensor );
    device->getMemoryManager()->getData(
            resTensor->getStartAddress(),
            0,
            12,
            reinterpret_cast<void*>(resf)
            );

    float corr[] = {3, 5, 7};

    for ( int j = 0; j < 3; j++ ) {
        EXPECT_FLOAT_EQ( corr[ j ], resf[ j ] );
    }

}

TEST( vm_test, vm_test_backprop_Test ) {
    Session sess;

    auto device = new CPUDevice();

    GenericExecutor executor(device);

    sess.setExecutor( &executor );

    TensorShape shape( { 1 } );

    auto a = new Tensor( shape, DataType::FLOAT );
    auto b = new Tensor( shape, DataType::FLOAT );

    float fa[] = {1};
    float fb[] = {2};

    auto ain = new InputNode( a, false );
    auto aInitializer = new DataInitializer();
    aInitializer->setData( reinterpret_cast<void*>(fa), sizeof( float ) );
    ain->setInitializer( aInitializer );

    auto bin = new InputNode( b, false );
    auto bInitializer = new DataInitializer();
    bInitializer->setData( reinterpret_cast<void*>(fb), sizeof( float ) );
    bin->setInitializer( bInitializer );

    auto logits = athena::ops::add( ain, bin );

    sess.prepare( logits );

    // todo Костыль. Нужен нормальный интерфейс
    device->getMemoryManager()->addTensor( a );
    device->getMemoryManager()->addTensor( b );

    float corr[] = {8};

    auto labelTensor = new Tensor( shape, DataType::FLOAT );

    auto labelNode = new InputNode( labelTensor );

    auto labelInitializer = new DataInitializer();
    labelInitializer->setData( reinterpret_cast<void*>(corr), sizeof( float ));
    labelNode->setInitializer( labelInitializer );

    auto loss = new MSELoss();
    loss->after( logits );
    loss->after( labelNode );

    auto gd = new GradientDescent( loss, 0.01 );
    gd->init( &sess );
    gd->prepare();

    device->getMemoryManager()->addTensor( labelTensor );

    auto resa = new float[1];
    auto resb = new float[1];

    sess.run();

    device->getMemoryManager()->loadAndLock( a );
    device->getMemoryManager()->getData(
            a->getStartAddress(),
            0,
            4,
            reinterpret_cast<void*>(resa)
    );
    device->getMemoryManager()->unlock( a->getStartAddress());

    device->getMemoryManager()->loadAndLock( b );
    device->getMemoryManager()->getData(
            b->getStartAddress(),
            0,
            4,
            reinterpret_cast<void*>(resb)
    );
    device->getMemoryManager()->unlock( b->getStartAddress());

    EXPECT_FLOAT_EQ(resa[0], 1);
    EXPECT_FLOAT_EQ(resb[0], 2);

    gd->minimize();



    device->getMemoryManager()->loadAndLock( a );
    device->getMemoryManager()->getData(
            a->getStartAddress(),
            0,
            4,
            reinterpret_cast<void*>(resa)
    );

    device->getMemoryManager()->loadAndLock( b );
    device->getMemoryManager()->getData(
            b->getStartAddress(),
            0,
            4,
            reinterpret_cast<void*>(resb)
    );


    EXPECT_FLOAT_EQ(resa[0], 3.5f);
    EXPECT_FLOAT_EQ(resb[0], 4.5f);

}
