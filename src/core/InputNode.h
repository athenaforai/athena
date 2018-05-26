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
    public:
        explicit InputNode(OpKernel *);

        /**
         * Check if it is an input node
         * @return true
         */
        bool isInputNode() override;

    };
}


#endif //ATHENA_INPUTNODE_H
