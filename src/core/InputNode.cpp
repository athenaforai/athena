//
// Created by Александр Баташев on 25.05.2018.
//

#include "InputNode.h"
#include <stdexcept>

bool athena::core::InputNode::isInputNode() {
    return true;
}

void athena::core::InputNode::setMappedMemCell(unsigned long cell) {
    mappedMemCell = cell;
}

unsigned long athena::core::InputNode::getMappedMemCell() {
    return mappedMemCell;
}

athena::core::Tensor *athena::core::InputNode::getData() {
    return this->input;
}

athena::core::InputNode *athena::core::InputNode::placeholder(const TensorShape &inputShape) {
    return new InputNode(inputShape);
}

void athena::core::InputNode::setData(athena::core::Tensor *data) {
    if (data != nullptr) {
        if (data->getShape() == initialShape) {
            this->input = data;
        } else {
            throw std::runtime_error("InputNode can't change its shape");
        }
    } else {
        this->input = nullptr;
    }
}
