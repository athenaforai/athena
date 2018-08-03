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

#include "CPUDevice.h"
#include <thread>

athena::backend::generic::CPUDevice::CPUDevice () : AbstractDevice() {
    maxThreads = std::thread::hardware_concurrency();
    activeThreads = 0;
    memorySize = 1024 * 1024; // 1 MB todo replace with real mem size
    memoryManager = new GenericMemoryManager();
    memoryManager->setMemSize( memorySize );
    memoryManager->init();
}

athena::backend::AbstractMemoryManager*
athena::backend::generic::CPUDevice::getMemoryManager () {
    return memoryManager;
}

athena::backend::generic::CPUDevice::~CPUDevice () {
    delete memoryManager;
}
