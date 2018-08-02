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

    void hadamardf ( GenericMemoryManager* memoryManager,
                    athena::core::Tensor* x,
                    athena::core::Tensor* y,
                    athena::core::Tensor* res ) {
        auto xData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(x->getStartAddress()));
        auto yData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(y->getStartAddress()));
        auto resData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

#pragma opm parallel for
        for ( unsigned long i = 0; i < x->getShape().totalSize(); i++ ) {
            resData[ i ] = xData[ i ] * yData[ i ];
        }
    }

    void hadamard ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* y,
                athena::core::Tensor* res ) {

        if ( x->getShape() != y->getShape()) {
            throw std::runtime_error( "Hadamard product is only defined for same-shaped"
                                      " Tensors" );
        }

        hadamardf( memoryManager, x, y, res );
    }
}