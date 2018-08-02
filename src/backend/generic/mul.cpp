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

#include <core/Tensor.h>
#include <core/DataType.h>
#include "ops.h"
#include "GenericMemoryManager.h"

namespace athena::backend::generic {

    void mul ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* a,
               athena::core::Tensor* b,
               athena::core::Tensor* res ) {

        if ( a->getShape().dimensions() == 1 ) {
            scale( memoryManager, a, b, res );
        } else if ( b->getShape().dimensions() == 1 ) {
            scale( memoryManager, b, a, res );
        } else if ( a->getShape().dimensions() == 2 && b->getShape().dimensions() == 2 ) {
            matmul( memoryManager, false, a, false, b, res );
        } else {
            throw std::runtime_error( "Tensor product is not implemented yet" );
        }

    }

}