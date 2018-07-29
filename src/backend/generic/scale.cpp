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


    inline void scalef ( GenericMemoryManager* memoryManager,
                         athena::core::Tensor* c,
                         athena::core::Tensor* src,
                         athena::core::Tensor* res ) {

        float fc = *reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress( c->getStartAddress()));

        auto fsrc = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress( src->getStartAddress()));

        auto fres = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress( res->getStartAddress()));

#pragma omp parallel for
        for ( unsigned long i = 0; i < src->getShape().totalSize(); i++ ) {
            fres[ i ] = fc * fsrc[ i ];
        }

    }

    inline void scaled ( GenericMemoryManager* memoryManager,
                         athena::core::Tensor* c,
                         athena::core::Tensor* src,
                         athena::core::Tensor* res ) {

        double dc = *reinterpret_cast<double*>(
                memoryManager->getPhysicalAddress( c->getStartAddress()));

        auto dsrc = reinterpret_cast<double*>(
                memoryManager->getPhysicalAddress( src->getStartAddress()));

        auto dres = reinterpret_cast<double*>(
                memoryManager->getPhysicalAddress( res->getStartAddress()));

#pragma omp parallel for
        for ( unsigned long i = 0; i < src->getShape().totalSize(); i++ ) {
            dres[ i ] = dc * dsrc[ i ];
        }

    }

    inline void scalei ( GenericMemoryManager* memoryManager,
                         athena::core::Tensor* c,
                         athena::core::Tensor* src,
                         athena::core::Tensor* res ) {

        int ic = *reinterpret_cast<int*>(
                memoryManager->getPhysicalAddress( c->getStartAddress()));

        auto isrc = reinterpret_cast<int*>(
                memoryManager->getPhysicalAddress( src->getStartAddress()));

        auto ires = reinterpret_cast<int*>(
                memoryManager->getPhysicalAddress( res->getStartAddress()));

#pragma omp parallel for
        for ( unsigned long i = 0; i < src->getShape().totalSize(); i++ ) {
            ires[ i ] = ic * isrc[ i ];
        }

    }


    void scale ( GenericMemoryManager* memoryManager,
                 athena::core::Tensor* c,
                 athena::core::Tensor* src,
                 athena::core::Tensor* res ) {
        if ( c == nullptr || src == nullptr ) {
            return;
        }

        if ( src->getType() == athena::core::DataType::DOUBLE ) {
            scaled( memoryManager, c, src, res );
        } else if ( src->getType() == athena::core::DataType::FLOAT ) {
            scalef( memoryManager, c, src, res );
        } else if ( src->getType() == athena::core::DataType::INT ) {
            scalei( memoryManager, c, src, res );
        }

    }
};

