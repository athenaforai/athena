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
        unsigned long mappedMemCell {};
        Tensor* input;
        bool _isFrozen;
    public:
//        explicit InputNode(OpKernel *);

        explicit InputNode ( Tensor* input, bool isFrozen = true ) : Node ( nullptr ),
                                                                     input ( input ),
                                                                     _isFrozen (
                                                                             isFrozen
                                                                     ) {};

        /**
         * Check if it is an input node
         * @return true
         */
        bool isInputNode () override;

        /**
         * Specify which memory cell will be used to store tensor for this node
         * @param cell Memory cell number
         */
        void setMappedMemCell ( unsigned long cell );

        /**
         * Get the number of memory cell that is used to store tensor for this node
         * @return Memory cell number
         */
        unsigned long getMappedMemCell ();

        /**
         * InputNodes can't be placed after other nodes in Athena's execution graph.
         * This method does nothing
         */
        void after ( Node* ) override {};

        /**
         * Get data associated with this InputNode
         * @return Pointer to Tensor
         */
        Tensor* getData ();

        /**
         * InputNodes can be frozen. This means their tensors won't be changed during
         * back propagation process (e.g. InputNode contains your input data).
         * By default new InputNodes are frozen.
         * @return Current freeze state
         */
        bool isFrozen ();

        /**
         * InputNodes can be frozen. This means their tensors won't be changed during
         * back propagation process (e.g. InputNode contains your input data).
         * By default new InputNodes are frozen.
         * @param frozen True - freeze node, False - unfreeze node (make it variable)
         */
        void setFrozen ( bool frozen );
    };
}


#endif //ATHENA_INPUTNODE_H
