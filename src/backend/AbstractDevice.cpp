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

#include "AbstractDevice.h"

unsigned long athena::backend::AbstractDevice::getMaxThreadMemSize () {
    return maxThreadMemorySize;
}

void athena::backend::AbstractDevice::setMaxThreadMemSize ( unsigned long size ) {
    if ( size == 0 ) {
        maxThreadMemorySize = memorySize / maxThreads;
    }
}
