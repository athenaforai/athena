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

#include "DataInitializer.h"

void athena::core::initializers::DataInitializer::initialize (
        athena::backend::AbstractMemoryManager* manager,
        athena::core::Tensor* tensor ) {

    manager->allocateAndLock( tensor );
    manager->setData( tensor->getStartAddress(), 0, length, data );
    manager->unlock( tensor->getStartAddress());

}

athena::core::initializers::DataInitializer::DataInitializer (
        const athena::core::initializers::DataInitializer &src ) {
    this->data = src.data;
}

athena::core::initializers::DataInitializer &
athena::core::initializers::DataInitializer::operator= (
        const athena::core::initializers::DataInitializer &src ) {
    this->data = src.data;
    return *this;
}

athena::core::initializers::DataInitializer::~DataInitializer () {
    data = nullptr;
}

void athena::core::initializers::DataInitializer::setData ( void* ptr, size_t length ) {
    this->data = ptr;
    this->length = length;
}
