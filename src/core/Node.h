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
        std::vector< Node* > incomingNodes;
        std::vector< Node* > outcomingNodes;
        OpKernel* operation;
        std::string name;

        std::string getRandomNodeName ();

        bool calculated;
        std::vector< vm_word > derivatives;
        unsigned long resultCell;

        unsigned long usageCount;

        bool persistResult;
    public:
        explicit Node ( OpKernel* );

        /**
         * Makes a new oriented edge in execution graph
         * from predecessor to this node
         * @param predecessor A predecessor node
         */
        virtual void after ( Node* predecessor );

        /**
         * Check if it is an input node
         * @return false
         */
        virtual bool isInputNode ();

        OpKernel* getOp ();

        std::vector< Node* > &getIncomingNodes ();

        std::string getName ();

        void addDerivative ( unsigned long d );

        vm_word getDerivative ( unsigned long i );

        void setCalculated ( unsigned long resCell );

        bool isCalculated ();

        vm_word getResult ();

        void updateUsageCount ();

        virtual bool isGarbage ();

        void setPersistResult();

    };
}


#endif //ATHENA_NODE_H
