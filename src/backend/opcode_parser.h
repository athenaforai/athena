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

#ifndef ATHENA_OPCODE_PARSER_H
#define ATHENA_OPCODE_PARSER_H

#include <backend/opcodes.h>
#include <vector>

namespace athena::backend {

    /**
     * Extract next command with its arguments from bytecode array (std::vector)
     * @param bytecode Vector with bytecode
     * @param next_word Start position to look through bytecode
     * @param new_word OpCode of the next word (Return value)
     * @param args Array of arguments (Return value) todo replace with vector
     * @param argc Number of args (Return value)
     * @return Position of next start value
     */
    unsigned int parse (
            std::vector< vm_word > &bytecode, unsigned long &next_word,
            OpCode &new_word, vm_word* args, unsigned long &argc
    );
}
#endif //ATHENA_OPCODE_PARSER_H
