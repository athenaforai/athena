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

    void sigmoidd ( GenericMemoryManager* memoryManager,
                    athena::core::Tensor* x,
                    athena::core::Tensor* res ) {
        auto data = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                x->getStartAddress()));
        auto newData = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            newData[ i ] = 1.0 / ( 1 + exp( -data[ i ] ));
        }
    }

    void sigmoidf ( GenericMemoryManager* memoryManager,
                    athena::core::Tensor* x,
                    athena::core::Tensor* res ) {
        auto data = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                x->getStartAddress()));
        auto newData = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            newData[ i ] = 1.0f / ( 1 + exp( -data[ i ] ));
        }

    }

    void sigmoid ( GenericMemoryManager* memoryManager,
                   athena::core::Tensor* x,
                   athena::core::Tensor* res ) {
        if ( x->getType() == athena::core::DataType::FLOAT ) {
            sigmoidf( memoryManager, x, res );
        } else if ( x->getType() == athena::core::DataType::DOUBLE ) {
            sigmoidd( memoryManager, x, res );
        }
    }


    void sigmoid_derivd ( GenericMemoryManager* memoryManager,
                                           athena::core::Tensor* x,
                                           athena::core::Tensor* res ) {
        auto data = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                x->getStartAddress()));
        auto newData = reinterpret_cast<double*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            double s = 1.0f / ( 1 + exp( -data[ i ] ));
            newData[ i ] = s * ( 1 - s );
        }

    }

    void sigmoid_derivf ( GenericMemoryManager* memoryManager,
                                           athena::core::Tensor* x,
                                           athena::core::Tensor* res ) {
        auto data = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                x->getStartAddress()));
        auto newData = reinterpret_cast<float*>(memoryManager->getPhysicalAddress(
                res->getStartAddress()));

        for ( int i = 0; i < x->getShape().totalSize(); i++ ) {
            float s = 1.0f / ( 1 + exp( -data[ i ] ));
            newData[ i ] = s * ( 1 - s );
        }
    }


    void sigmoid_deriv ( GenericMemoryManager* memoryManager,
                                          athena::core::Tensor* x,
                                          athena::core::Tensor* res ) {
        if ( x->getType() == athena::core::DataType::FLOAT ) {
            sigmoid_derivf( memoryManager, x, res );
        } else if ( x->getType() == athena::core::DataType::DOUBLE ) {
            sigmoid_derivd( memoryManager, x, res );
        }
    }
}

