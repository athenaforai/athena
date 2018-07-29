//
// Created by Александр Баташев on 27.05.2018.
//

#include <gtest/gtest.h>
#include <core/Tensor.h>
#include <backend/generic/ops.h>

using namespace athena::core;
using namespace athena::backend::generic;

TEST( add_op_test, add_1d ) {

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

    float f1[] = { 3 };

    gmm->setData( 1, 0, 4, f1 );

    gmm->unlock( tensor1->getStartAddress());


    gmm->addTensor( tensor2 );
    gmm->allocateAndLock( tensor2 );

    float f2[] = { 5 };

    gmm->setData( 5, 0, 4, f2 );

    gmm->unlock( tensor2->getStartAddress());


    gmm->addTensor( tensor3 );
    gmm->allocateAndLock( tensor3 );
    gmm->loadAndLock( tensor1 );
    gmm->loadAndLock( tensor2 );

    add( gmm, tensor1, tensor2, tensor3 );

    auto res = new float;

    gmm->getData( 9, 0, 4, res );

    gmm->unlock( tensor1->getStartAddress());
    gmm->unlock( tensor2->getStartAddress());
    gmm->unlock( tensor3->getStartAddress());

    ASSERT_FLOAT_EQ(*res, 8.0f);

    gmm->deinit();


//    size_t i[] = {3};
//    TensorShape shape(i, 1);
//    float af[] = {1, 2, 3};
//    Tensor a(shape, DataType::FLOAT, reinterpret_cast<u_char *>(af));
//
//    float bf[] = {4, 5, 6};
//    Tensor b(shape, DataType::FLOAT, reinterpret_cast<u_char *>(bf));
//
//    auto c = add(&a, &b);
//
//    float res[] = {5, 7, 9};
//    unsigned int idx[] = {0};
//    auto *cres = reinterpret_cast<unsigned char *>(res);
//    for (unsigned int j = 0; j < 3 * sizeof(float); j++) {
////        idx[0] = j;
//        EXPECT_EQ(cres[j], c->raw()[j]);
//    }
}
