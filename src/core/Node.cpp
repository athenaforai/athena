//
// Created by Александр Баташев on 25.05.2018.
//

#include "Node.h"

athena::core::Node::Node(OpKernel* operation) {
    this->operation = operation;
}

void athena::core::Node::after(athena::core::Node *predecessor) {
    if (predecessor != nullptr) {
        predecessor->outcomingNodes.push_back(this);
        incomingNodes.push_back(predecessor);
    }
}
