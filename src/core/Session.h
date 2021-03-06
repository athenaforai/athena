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

#pragma once
#ifndef ATHENA_SESSION_H
#define ATHENA_SESSION_H

#include "Node.h"
#include "InputNode.h"
#include <stack>
#include <backend/VirtualMemory.h>
#include <backend/AbstractExecutor.h>

namespace athena::core {
    /**
     * The class encapsulates everything needed for a single training step
     */
    class Session {
    private:
        /**
         * Contains references to all InputNodes in the graph
         */
        std::vector< InputNode* > headNodes;

        /**
         * Contains graph bytecode
         */
        std::vector< vm_word > bytecode;

        /**
         * Contains address of final result
         */
        vm_word resultCell;

        TensorShape resultShape;

        unsigned long maxMemSize;

        /**
         * Generates bytecode for sub-graph
         * @param logits sub-graph
         * @return bytecode
         */
        std::tuple< std::vector< vm_word >, TensorShape*, vm_word >
        getByteCode ( Node* logits );

        athena::backend::AbstractExecutor* executor {};

        athena::backend::VirtualMemory* virtualMemory;

    public:
        Session () : resultCell( 0 ), maxMemSize( 0 ),
                     virtualMemory( new athena::backend::VirtualMemory ) {};

        ~Session () = default;

        /**
         * Generates bytecode for the whole graph
         * @param logits
         */
        void prepare ( Node* logits );

        /**
         * does single training step
         * @return result tensor
         */
        Tensor* run ();

        unsigned long getResultCell ();

        void setExecutor ( athena::backend::AbstractExecutor* exec );

        athena::backend::AbstractExecutor* getExecutor();

        athena::backend::VirtualMemory* getMemory ();
    };
}


#endif //ATHENA_SESSION_H
