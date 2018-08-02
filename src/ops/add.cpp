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

#include "add.h"
#include <core/Node.h>
#include <core/kernels/AddOpKernel.h>

namespace athena::ops {

    athena::core::Node* add ( athena::core::Node* a, athena::core::Node* b ) {
        auto opker = new athena::core::kernels::AddOpKernel();
        auto node = new athena::core::Node( opker );

        node->after( a );
        node->after( b );

        return node;
    }

}