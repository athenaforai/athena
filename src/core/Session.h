//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_SESSION_H
#define ATHENA_SESSION_H

#include "Node.h"
#include "InputNode.h"
#include <stack>

namespace athena::core {
    class Session {
    private:
        std::vector<InputNode*> headNodes;
        std::vector<int> bytecode;
        int resultCell;

        std::vector<bool> memory_map;
        std::stack<int> free_mem;

        int maxMemSize;

        std::tuple<std::vector<int>, int> getByteCode(Node* logits);
        int getFreeMemCell();

    public:
        void prepare(Node * logits);
    };
}


#endif //ATHENA_SESSION_H
