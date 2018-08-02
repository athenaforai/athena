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

#include "AbstractMemoryManager.h"

void athena::backend::AbstractMemoryManager::resetTable () {
    tensors.clear();
}

void athena::backend::AbstractMemoryManager::addTensor ( athena::core::Tensor* tensor ) {
    tensors.push_back( tensor );
}

void
athena::backend::AbstractMemoryManager::loadAndLock ( athena::core::Tensor* tensor ) {
    loadAndLock( tensor->getStartAddress(), tensor->getShape().totalSize() *
                                            athena::core::typesize( tensor->getType()));
}

void athena::backend::AbstractMemoryManager::loadAndLock ( vm_word address ) {

    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            loadAndLock( t );
            break;
        }
    }

}

athena::core::Tensor*
athena::backend::AbstractMemoryManager::getTensor ( vm_word address ) {

    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            return t;
        }
    }

    return nullptr;
}

void
athena::backend::AbstractMemoryManager::allocateAndLock ( athena::core::Tensor* tensor ) {
    allocateAndLock( tensor->getStartAddress(),
                     athena::core::typesize( tensor->getType()) *
                     tensor->getShape().totalSize());
}

void athena::backend::AbstractMemoryManager::allocateAndLock ( vm_word address ) {
    for ( athena::core::Tensor* t : tensors ) {
        if ( t->getStartAddress() == address ) {
            allocateAndLock( t );
            break;
        }
    }
}
