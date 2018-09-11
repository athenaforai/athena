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

#ifndef ATHENA_CPUDEVICE_H
#define ATHENA_CPUDEVICE_H


#include <backend/AbstractDevice.h>
#include "GenericMemoryManager.h"

namespace athena::backend::generic {

    /**
     * This class represents a CPU
     * It encapsulates Memory Manager
     */
    class CPUDevice : public AbstractDevice {
    private:
        unsigned long activeThreads;
        GenericMemoryManager* memoryManager;
    public:
        CPUDevice ();
        ~CPUDevice ();

        AbstractMemoryManager* getMemoryManager() override ;

    };
}


#endif //ATHENA_CPUDEVICE_H
