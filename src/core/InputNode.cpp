//
// Created by Александр Баташев on 25.05.2018.
//

#include "InputNode.h"

//athena::core::InputNode::InputNode(athena::core::OpKernel *op) : Node(op) {
//}

bool athena::core::InputNode::isInputNode () {
    return true;
}

void athena::core::InputNode::setMappedMemCell ( unsigned long cell ) {
    mappedMemCell = cell;
}

unsigned long athena::core::InputNode::getMappedMemCell () {
    return mappedMemCell;
}

athena::core::Tensor* athena::core::InputNode::getData () {
    return this->input;
}

bool athena::core::InputNode::isFrozen () {
    return _isFrozen;
}

void athena::core::InputNode::setFrozen ( bool frozen ) {
    _isFrozen = frozen;
}

void athena::core::InputNode::setInitializer (
        athena::core::initializers::AbstractInitializer* initializer ) {
    this->initializer = initializer;
}

athena::core::initializers::AbstractInitializer*
athena::core::InputNode::getInitializer () {
    return initializer;
}