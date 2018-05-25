#ifndef ATHENA_NODE_H
#define ATHENA_NODE_H

#include <vector>
#include "OpKernel.h"
#include "Tensor.h"

namespace athena {
    namespace core {
        class Node {
        protected:
            std::vector<Node*> incomingNodes;
            std::vector<Node*> outcomingNodes;
            OpKernel* operation;
        public:
            Node(OpKernel*);
            void after(Node* predecessor);
        };
    }
}


#endif //ATHENA_NODE_H
