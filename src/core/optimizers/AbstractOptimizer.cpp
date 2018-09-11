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

#include "AbstractOptimizer.h"

void
athena::core::optimizers::AbstractOptimizer::init ( athena::core::Session* session ) {
    if ( session != nullptr ) {
        lastResultCell = session->getResultCell();
        this->session = session;
    }
}
