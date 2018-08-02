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

#ifndef ATHENA_DATATYPE_H
#define ATHENA_DATATYPE_H

namespace athena::core {

    /**
     * Data type for Tensor
     * FLOAT - single precision floating point number (32 bit)
     * DOUBLE - double precision floating point number (64 bit)
     * INT - signed integer number (32 bit)
     */
    enum class DataType : int {
        FLOAT = 0,
        DOUBLE = 1,
        INT = 2
    };

    unsigned int typesize ( DataType type );
}

#endif //ATHENA_DATATYPE_H
