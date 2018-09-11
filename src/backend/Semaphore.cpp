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

#include "Semaphore.h"

void athena::backend::Semaphore::enter () {
    std::unique_lock<decltype(mutex)> lock(mutex);
    while(!count) // Handle spurious wake-ups.
        condition.wait(lock);
    --count;
}

void athena::backend::Semaphore::leave () {
    std::unique_lock<decltype(mutex)> lock(mutex);
    ++count;
    condition.notify_one();
}
