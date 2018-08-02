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

#include "sigmoid.h"
#include <core/Node.h>
#include <core/kernels/SigmoidOpKernel.h>

namespace athena::ops {

    athena::core::Node* sigmoid ( athena::core::Node* x ) {
        auto opker = new athena::core::kernels::SigmoidOpKernel();
        auto node = new athena::core::Node( opker );

        node->after( x );

        return node;
    }
}