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

#include <gtest/gtest.h>
#include <backend/generic/GenericExecutor.h>

namespace athena::backend::generic {

    class GenericExecutorTest : public ::testing::Test {
    protected:

        GenericExecutor* executor{};

        void SetUp () override {
            auto device = new CPUDevice();
            executor = new GenericExecutor(device);
        }

        void TearDown() override {
            delete executor;
        };

    };
}