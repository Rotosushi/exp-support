// Copyright (C) 2025 cade-weinberg
//
// This file is part of exp-support.
//
// exp-support is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// exp-support is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with exp-support.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @file test/utility/test.h
 * @brief test macros.
 *
 * @note the common pattern for testing is to use an
 * integer which is incremented for each test. if a
 * test passes, the integer is incremented by zero.
 * if a test fails, the integer is incremented by one.
 *
 */

#ifndef SUPPORT_UTILITY_TEST_H
#define SUPPORT_UTILITY_TEST_H

#include "support/utility/message.h"

#define SUPPORT_TEST_ASSERT(count, condition)                                  \
    do {                                                                       \
        if (!(condition)) {                                                    \
            MessageInfo message_info = {                                       \
                .type    = MESSAGE_TYPE_ERROR,                                 \
                .line    = __LINE__,                                           \
                .file    = SV(__FILE__),                                       \
                .message = SV("test failed: " #condition),                     \
            };                                                                 \
            message(&message_info, stderr_stream);                             \
            count++;                                                           \
        }                                                                      \
    } while (0)

#endif // !SUPPORT_UTILITY_TEST_H
