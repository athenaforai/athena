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

#ifndef ATHENA_ABSTRACTLOSSFUNCTION_H
#define ATHENA_ABSTRACTLOSSFUNCTION_H


#include <core/Node.h>

namespace athena::core::loss {
    class AbstractLossFunction : public Node {
    public:
        AbstractLossFunction ( OpKernel* );

    };
}


#endif //ATHENA_ABSTRACTLOSSFUNCTION_H
