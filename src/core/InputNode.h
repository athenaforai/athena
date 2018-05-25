//
// Created by Александр Баташев on 25.05.2018.
//

#ifndef ATHENA_INPUTNODE_H
#define ATHENA_INPUTNODE_H

#include "Node.h"

namespace athena::core {
    class InputNode : public Node {
    public:
        InputNode(OpKernel *);
        bool isInputNode() override;

    };
}


#endif //ATHENA_INPUTNODE_H
