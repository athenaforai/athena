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

#ifndef ATHENA_TENSORSHAPE_H
#define ATHENA_TENSORSHAPE_H

#include <vector>
#include <array>
#include <utility>
#include <backend/opcodes.h>

namespace athena::core {

    /**
     * Class represents size parameters for Tensor
     */
    class TensorShape {
    private:
        std::vector< vm_word > shape;
    public:
        explicit TensorShape ( std::vector< vm_word > shape ) :
                shape( std::move( shape )) {};

        TensorShape() = default;

        TensorShape ( unsigned long* shape, unsigned long length );

        TensorShape ( const TensorShape & );

        TensorShape &operator= ( const TensorShape & );

        /**
         * @return Number of dimensions in Tensor
         */
        unsigned long dimensions () const;

        /**
         * Gives size for certain dimension
         * @param n Dimension index ( 0 <= d < dimensions )
         * @return Size of dimension n
         */
        unsigned long dim ( unsigned long n ) const;

        /**
         * @return Total number of elements in Tensor
         */
        unsigned long totalSize () const;

        const std::vector< vm_word > &getShape () const;

        /**
         * @return True if dimensions are equal, else False
         */
        bool operator== ( const TensorShape & ) const;

        /**
         * @param rhs TensorShape to be compared with
         * @return True if dimensions are different, else False
         */
        bool operator!= ( const TensorShape &rhs ) const;
    };
}


#endif //ATHENA_TENSORSHAPE_H
