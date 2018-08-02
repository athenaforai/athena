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

namespace athena::backend::generic {

    void copy ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* res ) {
        if ( x != nullptr ) {
            unsigned long total =
                    static_cast<unsigned int>(
                            athena::core::typesize( x->getType()) *
                            x->getShape().totalSize());

            auto newData = reinterpret_cast<unsigned char*>(
                    memoryManager->getPhysicalAddress( res->getStartAddress())
            );
            auto data = reinterpret_cast<unsigned char*>(
                    memoryManager->getPhysicalAddress( x->getStartAddress())
            );

#pragma omp parallel for
            for ( unsigned long i = 0; i < total; i++ ) {
                newData[ i ] = data[ i ];
            }

        }
    }

}