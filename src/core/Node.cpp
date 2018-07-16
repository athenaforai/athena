//
// Created by Александр Баташев on 25.05.2018.
//

#include "Node.h"

athena::core::Node::Node ( OpKernel* operation ) :
        operation( operation ), derivativeMark( false ),
        calculated( false ), resultCell( 0 ), usageCount( 0 ) {
    name = getRandomNodeName();
}

void athena::core::Node::after ( athena::core::Node* predecessor ) {
    if ( predecessor != nullptr ) {
        predecessor->outcomingNodes.push_back( this );
        incomingNodes.push_back( predecessor );
    }
}

std::string athena::core::Node::getRandomNodeName () {
    return "random_name";
}

bool athena::core::Node::isInputNode () {
    return false;
}

athena::core::OpKernel* athena::core::Node::getOp () {
    return this->operation;
}

std::vector< athena::core::Node* > &athena::core::Node::getIncomingNodes () {
    return incomingNodes;
}

std::string athena::core::Node::getName () {
    return name;
}

void athena::core::Node::addDerivative ( unsigned long d ) {
    derivatives.push_back( d );
}

vm_word athena::core::Node::getDerivative ( int i ) {
    return derivatives[ i ];
}

void athena::core::Node::setCalculated ( unsigned long resCell ) {
    resultCell = resCell;
    calculated = true;
}

bool athena::core::Node::isCalculated () {
    return calculated;
}

vm_word athena::core::Node::getResult () {
    return resultCell;
}

void athena::core::Node::updateUsageCount () {
    usageCount++;
}

bool athena::core::Node::isGarbage () {
    return usageCount == outcomingNodes.size();
}
