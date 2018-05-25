//
// Created by Александр Баташев on 25.05.2018.
//

#include "InputNode.h"

athena::core::InputNode::InputNode(athena::core::OpKernel *op) : Node(op) {
}

bool athena::core::InputNode::isInputNode() {
    return true;
}
