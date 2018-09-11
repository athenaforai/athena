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
#include "GenericMemoryManager.h"

namespace athena::backend::generic {

    void addf ( GenericMemoryManager* memoryManager,
                                 athena::core::Tensor* a,
                                 athena::core::Tensor* b,
                                 athena::core::Tensor* res ) {
        // todo find optimizations
        auto af = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < b->getShape().dim( 0 ); i++ ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
    }

    void addd ( GenericMemoryManager* memoryManager,
                                 athena::core::Tensor* a,
                                 athena::core::Tensor* b,
                                 athena::core::Tensor* res ) {
        auto af = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < b->getShape().dim( 0 ); i++ ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
    }

    void addi ( GenericMemoryManager* memoryManager,
                athena::core::Tensor* a,
                athena::core::Tensor* b,
                athena::core::Tensor* res ) {
        auto af = reinterpret_cast<int*>(memoryManager->getPhysicalAddress(
                a->getStartAddress()));
        auto bf = reinterpret_cast<int*>(memoryManager->getPhysicalAddress(
                b->getStartAddress()));
        auto cf = reinterpret_cast<int*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < b->getShape().dim( 0 ); i++ ) {
            cf[ i ] = af[ i ] + bf[ i ];
        }
    }

    void add ( GenericMemoryManager* memoryManager,
                                athena::core::Tensor* a,
                                athena::core::Tensor* b,
                                athena::core::Tensor* res
    ) {

        if ( a->getShape() == b->getShape()) {
            switch ( a->getType()) {
                case athena::core::DataType::FLOAT:
                    addf( memoryManager, a, b, res );
                    break;
                case athena::core::DataType::DOUBLE:
                    addd( memoryManager, a, b, res );
                    break;
                case athena::core::DataType::INT:
                    addi( memoryManager, a, b, res );
                    break;
            }
        }
    }
}