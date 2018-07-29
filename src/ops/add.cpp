//
// Created by Александр Баташев on 25.05.2018.
//

#include "add.h"
#include <core/Node.h>
#include <core/kernels/AddOpKernel.h>

namespace athena::ops {

    athena::core::Node* add ( athena::core::Node* a, athena::core::Node* b ) {
        auto opker = new athena::core::kernels::AddOpKernel();
        auto node = new athena::core::Node( opker );

        node->after( a );
        node->after( b );

        return node;
    }

}