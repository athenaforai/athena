//
// Created by Александр Баташев on 28.06.2018.
//

#include <queue>
#include "GradientDescent.h"

athena::core::optimizers::GradientDescent::GradientDescent(AbstractLossFunction* loss, float learningRate)
        : AbstractOptimizer(loss), learningRate(learningRate) {}


void athena::core::optimizers::GradientDescent::prepare() {

    if (loss != nullptr) {
        auto[bytecode, resultCell] = getByteCode(loss);
        this->bytecode.clear();
        this->bytecode.insert(std::end(this->bytecode), std::begin(bytecode), std::end(bytecode));
    }

}

std::tuple<std::vector<unsigned long>, unsigned long>
athena::core::optimizers::GradientDescent::getByteCode(AbstractLossFunction* node) {

    std::vector<unsigned long> bytecode;

    unsigned long errorCell = this->session->getFreeMemCell();
    std::vector<unsigned long> lossArgs(1);
    lossArgs.push_back(lastResultCell);
    node->getOp()->getOpBytecode(lossArgs, errorCell);

    std::queue<Node *> nodesQueue;
    nodesQueue.push(node);
    std::queue<unsigned long> errorCells;
    errorCells.push(errorCell);

    while (!nodesQueue.empty()) {
        Node* curNode = nodesQueue.front();
        nodesQueue.pop();

        curNode->setDerivativeMarked();

        for (int i = 0; i < curNode->getIncomingNodes().size(); i++) {
            
        }
    }

    return std::make_tuple(bytecode, static_cast<unsigned long>(0));
}
