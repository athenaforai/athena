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
        unsigned long mappedMemCell{};
        Tensor *input;
        TensorShape initialShape;

        InputNode(const TensorShape &inputShape) : Node(nullptr), input(nullptr),
                                                   initialShape(TensorShape(initialShape)) {};
    public:
        explicit InputNode(Tensor *input) : Node(nullptr), input(input),
                                            initialShape(TensorShape(input->getShape())) {};

        /**
         * Creates an InputNode without data
         * @param inputShape TensorShape of your future data
         * @return Pointer to an InputShape without data
         */
        static InputNode *placeholder(const TensorShape &inputShape);

        /**
         * Check if it is an input node
         * @return true
         */
        bool isInputNode() override;

        void setMappedMemCell(unsigned long cell);

        unsigned long getMappedMemCell();

        void after(Node *) override {};

        Tensor *getData();

        void setData(Tensor *data);
    };
}


#endif //ATHENA_INPUTNODE_H
