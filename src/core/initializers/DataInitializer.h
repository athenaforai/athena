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

#pragma once
#ifndef ATHENA_DATAINITIALIZER_H
#define ATHENA_DATAINITIALIZER_H

#include <cstddef>
#include "AbstractInitializer.h"
#include <backend/AbstractMemoryManager.h>

namespace athena::core::initializers {
    class DataInitializer : public AbstractInitializer {
    private:
        void *data;
        size_t length;
    public:

        DataInitializer() : data( nullptr), length(0) {}

        DataInitializer ( const DataInitializer &src );

        DataInitializer &operator= ( const DataInitializer &src );

        ~DataInitializer ();

        void setData ( void* ptr, size_t length );

        void initialize ( athena::backend::AbstractMemoryManager* manager,
                          Tensor* tensor ) override;
    };
}


#endif //ATHENA_DATAINITIALIZER_H
