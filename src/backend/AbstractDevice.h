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

#ifndef ATHENA_ABSTRACTDEVICE_H
#define ATHENA_ABSTRACTDEVICE_H

#include "AbstractMemoryManager.h"

namespace athena::backend {
    class AbstractDevice {
    protected:
        unsigned long maxThreadMemorySize;
        unsigned long maxThreads;
        unsigned long memorySize;
    public:
        unsigned long getMaxThreadMemSize ();

        void setMaxThreadMemSize ( unsigned long size = 0 );

        virtual AbstractMemoryManager* getMemoryManager() = 0;
    };
}


#endif //ATHENA_ABSTRACTDEVICE_H
