//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_SESSION_H
#define ATHENA_SESSION_H

#include "Node.h"
#include "InputNode.h"

namespace athena {
    namespace core {
        class Session {
        private:
            std::vector<InputNode*> headNodes;
        public:
            void prepare(Node * logits);
        };
    }
}


#endif //ATHENA_SESSION_H
