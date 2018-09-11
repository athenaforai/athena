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

#ifndef ATHENA_SEMAPHORE_H
#define ATHENA_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

namespace athena::backend {
    class Semaphore {
    private:
        std::mutex mutex;
        std::condition_variable condition;
        unsigned long count = 0;

    public:
        void enter ();

        void leave ();
    };
}

#endif //ATHENA_SEMAPHORE_H
