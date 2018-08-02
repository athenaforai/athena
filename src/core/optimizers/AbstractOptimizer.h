/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://athenaproject.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#ifndef ATHENA_ABSTRACTOPTIMIZER_H
#define ATHENA_ABSTRACTOPTIMIZER_H


#include <core/InputNode.h>
#include <core/loss/AbstractLossFunction.h>
#include <core/Session.h>
#include "core/Node.h"

namespace athena::core::optimizers {
    class AbstractOptimizer {
    protected:
        std::vector< InputNode* > headNodes;
        std::vector< vm_word > bytecode;

        unsigned long lastResultCell;
        Session* session;

        athena::core::loss::AbstractLossFunction* loss;
    public:
        explicit AbstractOptimizer ( athena::core::loss::AbstractLossFunction* loss ) : loss( loss ),
                                                                    lastResultCell( 0 ),
                                                                    session(
                                                                            nullptr
                                                                    ) {};

        ~AbstractOptimizer () = default;

        void init ( Session* session );

        virtual void prepare () = 0;

        virtual void minimize () = 0;
    };
}


#endif //ATHENA_ABSTRACTOPTIMIZER_H
