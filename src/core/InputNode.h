//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_INPUTNODE_H
#define ATHENA_INPUTNODE_H

#include "Node.h"

namespace athena::core {
    /**
     * Subclass of athena::core::Node
     * Represents a node that has no predecessors
     */
    class InputNode : public Node {
    private:
        unsigned long mappedMemCell;
        Tensor* input;
    public:
//        explicit InputNode(OpKernel *);

        explicit InputNode(Tensor * input) : Node(nullptr), input(input){};

        /**
         * Check if it is an input node
         * @return true
         */
        bool isInputNode() override;

        void setMappedMemCell(unsigned long cell);
        unsigned long getMappedMemCell();

        void after(Node*) override {};

        Tensor* getData();
    };
}


#endif //ATHENA_INPUTNODE_H
