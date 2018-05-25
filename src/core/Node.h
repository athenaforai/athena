#ifndef ATHENA_NODE_H
#define ATHENA_NODE_H

#include <vector>
#include <string>
#include "OpKernel.h"
#include "Tensor.h"

namespace athena::core {
    class Node {
    protected:
        std::vector<Node*> incomingNodes;
        std::vector<Node*> outcomingNodes;
        OpKernel* operation;
        std::string name;
        std::string getRandomNodeName();
    public:
        Node(OpKernel*);
        void after(Node* predecessor);
        bool isInputNode();
    };
}


#endif //ATHENA_NODE_H
