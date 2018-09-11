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

#include <iostream>
#include "TensorShape.h"

unsigned long athena::core::TensorShape::totalSize () const {
    unsigned long ts = 1;
    for ( unsigned long i : shape ) {
        ts *= i;
    }
    return ts;
}

athena::core::TensorShape::TensorShape ( vm_word* shape, unsigned long length ) {
//    this->shape.insert( std::end( this->shape ), shape,
//                         static_cast<const vm_word>(shape + length));
    for( unsigned long i = 0; i < length; i++) {
        this->shape.push_back(shape[i]);
    }
}

unsigned long athena::core::TensorShape::dimensions () const {
    return shape.size();
}

unsigned long athena::core::TensorShape::dim ( unsigned long n ) const {
    return n < shape.size() ? shape[ n ] : 0;
}

const std::vector< unsigned long > &athena::core::TensorShape::getShape () const {
    return shape;
}

bool
athena::core::TensorShape::operator== ( const athena::core::TensorShape &rhs ) const {
    if ( dimensions() != rhs.dimensions()) {
        return false;
    } else {
        for ( unsigned long i = 0; i < dimensions(); i++ ) {
            if ( dim( i ) != rhs.dim( i )) {
                return false;
            }
        }
    }
    return true;
}

bool
athena::core::TensorShape::operator!= ( const athena::core::TensorShape &rhs ) const {
    return !( *this == rhs );
}

athena::core::TensorShape::TensorShape ( const athena::core::TensorShape & src) {
    this->shape = src.shape;

}

athena::core::TensorShape &
athena::core::TensorShape::operator= ( const athena::core::TensorShape &src ) {
    if ( this != &src ) {
        this->shape = src.shape;
    }
    return *this;
}
