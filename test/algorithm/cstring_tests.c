/**
 * Copyright (C) 2025 cade-weinberg
 *
 * This file is part of support.
 *
 * support is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * support is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with support.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file test/algorithm/cstring_tests.c
 * @brief tests for the cstring functions.
 */

#include "support/algorithm/cstring.h"
#include "support/algorithm/memory.h"
#include "support/utility/null.h"
#include "support/utility/test.h"

i32 test_cstring_length() {
    i32  count      = 0;
    char cstring[6] = "hello";
    u64  length     = 0;

    {
        Result result = cstring_length(cstring, &length);
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count, length == 5);
    }

    {
        char  *null_cstring = NULL;
        Result result       = cstring_length(null_cstring, &length);
        SUPPORT_TEST_ASSERT(count, result == RESULT_NULL_SOURCE);
    }

    {
        Result result = cstring_length(cstring, NULL);
        SUPPORT_TEST_ASSERT(count, result == RESULT_NULL_TARGET);
    }

    return count;
}

i32 main() {
    i32 count = 0;

    count += test_cstring_length();

    return count;
}
