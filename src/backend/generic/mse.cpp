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
#include <cmath>

namespace athena::backend::generic {

    void msef ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res ) {

        auto xData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(x->getStartAddress()));
        auto yData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(y->getStartAddress()));
        auto resData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

#pragma omp parallel for
        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            resData[ 0 ] += std::pow( xData[ i ] - yData[ i ], 2.0f );
        }

    }

    void mse ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res ) {

        // todo types
        msef(memoryManager, x, y, res);

    }


    void mse_derivf ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* x,
                athena::core::Tensor* y,
                athena::core::Tensor* res ) {

        auto xData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(x->getStartAddress()));
        auto yData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(y->getStartAddress()));
        auto resData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

#pragma omp parallel for
        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            resData[ i ] = 2 * (xData[ i ] - yData[ i ] );
        }

    }

    void mse_deriv ( GenericMemoryManager* memoryManager,
               athena::core::Tensor* x,
               athena::core::Tensor* y,
               athena::core::Tensor* res ) {

        // todo types
        mse_derivf(memoryManager, x, y, res);

    }

}