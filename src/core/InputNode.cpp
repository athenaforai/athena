//
// Created by Александр Баташев on 25.05.2018.
//

#include "InputNode.h"

athena::core::InputNode::InputNode(athena::core::OpKernel *op) : Node(op) {
}

bool athena::core::InputNode::isInputNode() {
    return true;
}

void athena::core::InputNode::setMappedMemCell(int cell) {
    mappedMemCell = cell;
}

int athena::core::InputNode::getMappedMemCell() {
    return mappedMemCell;
}
