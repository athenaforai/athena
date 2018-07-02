//
// Created by Александр Баташев on 01.07.2018.
//

#include "sigmoid.h"
#include <core/Node.h>
#include <core/kernels/SigmoidOpKernel.h>

namespace athena::ops {

    athena::core::Node* sigmoid ( athena::core::Node* x ){
        auto opker = new athena::core::kernels::SigmoidOpKernel ();
        auto node = new athena::core::Node ( opker );

        node->after ( x );

        return node;
    }
}