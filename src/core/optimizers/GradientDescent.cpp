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
    nodesQueue.push(node->getIncomingNodes()[0]);
    std::queue<unsigned long> errorCells;
    errorCells.push(errorCell);

    while (!nodesQueue.empty()) {
        Node* curNode = nodesQueue.front();
        nodesQueue.pop();

        for (int i = 0; i < curNode->getIncomingNodes().size(); i++) {
            Node *inNode = curNode->getIncomingNodes()[i];
            unsigned long err = errorCells.front();
            errorCells.pop();

            unsigned long newErr = session->getFreeMemCell();

            bytecode.push_back(static_cast<unsigned long>(OpCode::MATMUL));
            bytecode.push_back(err);
            bytecode.push_back(curNode->getDerivative(i));
            bytecode.push_back(newErr);

            errorCells.push(newErr);

            if (inNode->isInputNode()) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
                auto inputNode = dynamic_cast<InputNode*>(inNode);
                if (!inputNode->isFrozen()) {
                    bytecode.push_back(static_cast<unsigned long>(OpCode::SCALE));
                    bytecode.push_back(reinterpret_cast<unsigned long>(-1*learningRate));
                    bytecode.push_back(newErr);
                    unsigned long delta = session->getFreeMemCell();
                    bytecode.push_back(delta);

                    bytecode.push_back(static_cast<unsigned long>(OpCode::ADD));
                    bytecode.push_back(inputNode->getMappedMemCell());
                    bytecode.push_back(delta);
                    bytecode.push_back(inputNode->getMappedMemCell());
                }
#pragma clang diagnostic pop
            } else {
                nodesQueue.push(inNode);
            }
        }

        /*
         * todo:
         * for every incoming node
         * 1) Pop error from errorCells
         * 2) Multiply error cell by corresponding derivative of curNode
         * 3) Push result back to queue
         * 4) If current incoming node is InputNode and it is not frozen, update values
         * 5) Else push current incoming node to queue
         */
    }

    return std::make_tuple(bytecode, static_cast<unsigned long>(0));
}
