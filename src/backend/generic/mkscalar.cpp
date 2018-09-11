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

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include <cstring>

namespace athena::backend::generic {

    void mkscalar ( GenericMemoryManager* memoryManager,
                    unsigned long s,
                    athena::core::Tensor* res ) {
        auto scalar = reinterpret_cast<float*>(&s);
        auto f = memoryManager->getPhysicalAddress( res->getStartAddress());
        memcpy( f, scalar, sizeof( float ));
    }
}