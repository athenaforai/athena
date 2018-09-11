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

#include "InputNode.h"

bool athena::core::InputNode::isInputNode () {
    return true;
}

void athena::core::InputNode::setMappedMemCell ( unsigned long cell ) {
    mappedMemCell = cell;
}

unsigned long athena::core::InputNode::getMappedMemCell () {
    return mappedMemCell;
}

athena::core::Tensor* athena::core::InputNode::getData () {
    return this->input;
}

bool athena::core::InputNode::isFrozen () {
    return _isFrozen;
}

void athena::core::InputNode::setFrozen ( bool frozen ) {
    _isFrozen = frozen;
}

void athena::core::InputNode::setInitializer (
        athena::core::initializers::AbstractInitializer* initializer ) {
    this->initializer = initializer;
}

athena::core::initializers::AbstractInitializer*
athena::core::InputNode::getInitializer () {
    return initializer;
}

bool athena::core::InputNode::isGarbage () {
    return false;
}
