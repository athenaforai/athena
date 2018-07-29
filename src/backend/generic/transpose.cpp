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

    void transposef ( GenericMemoryManager* memoryManager,
                     athena::core::Tensor* a,
                     athena::core::Tensor* res ) {
        auto data = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(a->getStartAddress()));
        auto transposedData = reinterpret_cast<float*>(
                memoryManager->getPhysicalAddress(res->getStartAddress()));

        size_t m = a->getShape().dim( 1 );

#pragma omp parallel for
        for ( int n = 0; n < a->getShape().totalSize(); n++ ) {
            auto i = static_cast<int>(n / a->getShape().dim( 0 ));
            auto j = static_cast<int>(n % a->getShape().dim( 0 ));

            transposedData[ n ] = data[ m * j + i ];
        }

        athena::core::TensorShape shape( { m, a->getShape().dim( 0 ) } );
    }


    /*
     * see https://stackoverflow.com/questions/16737298/what-is-the-fastest-way-to-transpose-a-matrix-in-c
     * for better solution
     */
    void transpose ( GenericMemoryManager* memoryManager,
                     athena::core::Tensor* a,
                     athena::core::Tensor* res ) {

        // todo improve speed, types
        if ( a != nullptr ) {
            if ( a->getType() == athena::core::DataType::FLOAT ) {
                transposef( memoryManager, a, res );
            }
        }
    }

}