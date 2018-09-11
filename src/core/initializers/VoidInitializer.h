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

#ifndef ATHENA_VOIDINITIALIZER_H
#define ATHENA_VOIDINITIALIZER_H

#include "AbstractInitializer.h"

namespace athena::core::initializers {

    /**
     * VoidInitializer is the simplest initializer possible. It does not initialize
     * Tensor in any way. It is the default initializer for newly created Tensor
     */
    class VoidInitializer : public AbstractInitializer {
    public:
        void initialize ( athena::backend::AbstractMemoryManager*,
                          Tensor* ) override;
    };
}


#endif //ATHENA_VOIDINITIALIZER_H
