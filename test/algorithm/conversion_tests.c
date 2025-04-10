/**
 * Copyright (C) 2025 cade-weinberg
 *
 * This file is part of exp-support.
 *
 * exp-support is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * exp-support is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with exp-support.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file test/algorithm/conversion_tests.c
 * @brief tests for the conversion functions.
 */

#include "support/algorithm/conversion.h"
#include "support/algorithm/memory.h"
#include "support/utility/null.h"
#include "support/utility/test.h"

static i32 test_convert_base_10_u64() {
    i32  count      = 0;
    char buffer[20] = {0};
    u64  value      = 1234567890123456789;

    {
        u64 buffer_length = convert_base_10_u64_buffer_length(value);
        SUPPORT_TEST_ASSERT(count, buffer_length == 19);
    }

    {
        i32    cmp    = 0;
        Result result = convert_base_10_u64(value, buffer, sizeof(buffer));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count,
                            memory_compare(buffer,
                                           sizeof(buffer),
                                           "1234567890123456789",
                                           20,
                                           sizeof(buffer),
                                           &cmp) == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count, cmp == 0);
    }

    return count;
}

static i32 test_convert_base_10_i64() {
    i32  count      = 0;
    char buffer[20] = {0};
    i64  value      = -1234567890123456789;

    {
        u64 buffer_length = convert_base_10_i64_buffer_length(value);
        SUPPORT_TEST_ASSERT(count, buffer_length == 20);
    }

    {
        i32    cmp    = 0;
        Result result = convert_base_10_i64(value, buffer, sizeof(buffer));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count,
                            memory_compare(buffer,
                                           sizeof(buffer),
                                           "-1234567890123456789",
                                           20,
                                           sizeof(buffer),
                                           &cmp) == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count, cmp == 0);
    }

    return count;
}

i32 main() {
    i32 count = 0;

    count += test_convert_base_10_u64();
    count += test_convert_base_10_i64();

    return count;
}
