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

#ifndef ATHENA_VMSTATE_H
#define ATHENA_VMSTATE_H

namespace athena::backend {

    /**
     * VMState structure describes current state of executor thread
     */
    struct VMState {

        /**
         * Batch Counter, number of batches
         */
        unsigned long BC = 1;

        /**
         * Batch Pointer, number of current batch
         */
        unsigned long BP = 0;

        /**
         * Instruction Pointer, points to instruction that is going to be executed
         */
        unsigned long IP = 0;



    };

}

#endif //ATHENA_VMSTATE_H
