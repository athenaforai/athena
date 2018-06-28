#ifndef ATHENA_NODE_H
#define ATHENA_NODE_H

#include <vector>
#include <string>
#include "OpKernel.h"
#include "Tensor.h"

namespace athena::core {
    /**
     * A basic element of execution graph
     * Each node has pointers to its predecessors
     * and successors. It encapsulates operation
     * and data.
     */
    class Node {
    protected:
        std::vector<Node*> incomingNodes;
        std::vector<Node*> outcomingNodes;
        OpKernel* operation;
        std::string name;
        std::string getRandomNodeName();

        bool derivativeMark;
    public:
        explicit Node(OpKernel*) : derivativeMark(false) {};

        /**
         * Makes a new oriented edge in execution graph
         * from predecessor to this node
         * @param predecessor A predecessor node
         */
        virtual void after(Node* predecessor);

        /**
         * Check if it is an input node
         * @return false
         */
        virtual bool isInputNode();

        OpKernel* getOp();

        std::vector<Node*>& getIncomingNodes();

        std::string getName();

        bool isDerivativeMarked();
        void setDerivativeMarked();
    };
}


#endif //ATHENA_NODE_H
