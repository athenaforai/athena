//
// Created by Александр Баташев on 27.05.2018.
//

#include <gtest/gtest.h>
#include <core/Session.h>
#include <core/Tensor.h>
#include <core/InputNode.h>
#include <ops/ops.h>
#include <core/loss/MSELoss.h>
#include <core/optimizers/GradientDescent.h>
#include <backend/generic/CPUDevice.h>
#include <backend/generic/GenericExecutor.h>

using namespace athena::core;
using namespace athena::core::loss;
using namespace athena::core::optimizers;

using namespace athena::backend::generic;

TEST( vm_test, vm_test_simple_Test ) {
    Session sess;

    CPUDevice device;

    GenericExecutor executor(&device);

    sess.setExecutor( &executor );

    dynamic_cast<GenericMemoryManager*>(device.getMemoryManager())->init();

    TensorShape shape( { 3 } );

    auto a = new Tensor( shape, DataType::FLOAT );
    auto b = new Tensor( shape, DataType::FLOAT );

    auto ain = new InputNode( a );
    auto bin = new InputNode( b );

    auto logits = athena::ops::add( ain, bin );

    sess.prepare( logits );

    // todo Костыль. Нужен нормальный интерфейс
    device.getMemoryManager()->addTensor( a );
    device.getMemoryManager()->addTensor( b );

    sess.run();

//    size_t shapeArr[] = { 3 };
//    TensorShape shape( shapeArr, 1 );
//
//    float af[] = { 1, 2, 3 };
//    float bf[] = { 2, 3, 4 };
//
//    auto* a = new Tensor( shape, DataType::FLOAT, reinterpret_cast<u_char*>(af));
//    auto* b = new Tensor( shape, DataType::FLOAT, reinterpret_cast<u_char*>(bf));
//
//    auto an = InputNode( a );
//    auto bn = InputNode( b );
//
//    auto logits = athena::ops::add( &an, &bn );
//
//    sess.prepare( logits );
//    auto res = sess.run();
//
//    float resf[] = { 3, 5, 7 };
//    auto resc = reinterpret_cast<float*>(res->raw());
//
//    for ( int j = 0; j < 3; j++ ) {
//        EXPECT_FLOAT_EQ( resc[ j ], resf[ j ] );
//    }

}

TEST( vm_test, vm_test_backprop_Test ) {
//    Session sess;
//
//    size_t shapeArr[] = { 3 };
//    TensorShape shape( shapeArr, 1 );
//
//    float af[] = { 1, 2, 3 };
//    float bf[] = { 2, 3, 4 };
//    float lf[] = { 6, 7, 8 };
//
//    auto* a = new Tensor( shape, DataType::FLOAT, reinterpret_cast<u_char*>(af));
//    auto* b = new Tensor( shape, DataType::FLOAT, reinterpret_cast<u_char*>(bf));
//
//    auto an = InputNode( a, false );
//    auto bn = InputNode( b, true );
//
//    auto logits = athena::ops::add( &an, &bn );
//
//    MSELoss loss1;
//    loss1.after( logits );
//
//    auto labels = new Tensor( shape, DataType::FLOAT, reinterpret_cast<u_char*>(lf));
//    loss1.after( new InputNode( labels ));
//
//    GradientDescent gd( &loss1, 0.01 );
//
//    sess.prepare( logits );
//    gd.init( &sess );
//    gd.prepare();
//    auto res = sess.run();
//
//    float resf[] = { 3, 5, 7 };
//    auto resc = reinterpret_cast<float*>(res->raw());
//
//    for ( int j = 0; j < 3; j++ ) {
//        EXPECT_FLOAT_EQ( resc[ j ], resf[ j ] );
//    }
//
//    gd.minimize();


}