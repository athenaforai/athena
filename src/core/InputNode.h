/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaframework.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#ifndef ATHENA_INPUTNODE_H
#define ATHENA_INPUTNODE_H

#include <core/initializers/AbstractInitializer.h>
#include <core/initializers/VoidInitializer.h>
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
        athena::core::initializers::AbstractInitializer* initializer;
    public:
//        explicit InputNode(OpKernel *);

        explicit InputNode ( Tensor* input, bool isFrozen = true ) :
                Node( nullptr ),
                input( input ),
                _isFrozen( isFrozen ),
                initializer( new athena::core::initializers::VoidInitializer()) {};

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

        void
        setInitializer ( athena::core::initializers::AbstractInitializer* initializer );

        athena::core::initializers::AbstractInitializer* getInitializer ();

        bool isGarbage() override;
    };
}


#endif //ATHENA_INPUTNODE_H
