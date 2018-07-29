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

#include "Tensor.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace athena::core {

    const TensorShape &Tensor::getShape () const {
        return shape;
    }

    DataType Tensor::getType () const {
        return dataType;
    }

    vm_word Tensor::getStartAddress () {
        return startAddress;
    }

    Tensor &Tensor::operator[] ( unsigned int idx ) {
        std::vector<unsigned long> dims;

        for ( int i = 1; i < shape.dimensions(); i++ ) {
            dims.push_back( shape.dim( static_cast<unsigned long>(i)));
        }

        Tensor* res = new Tensor( TensorShape( dims ), dataType );
        res->startAddress =
                startAddress + idx * res->shape.totalSize() * typesize( dataType );

        return *res;
    }

    void Tensor::setStartAddress ( vm_word address ) {
        startAddress = address;
    }

}
