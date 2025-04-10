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
 * @file test/algorithm/memory_tests.c
 * @brief tests for the memory functions.
 */

#include "support/algorithm/memory.h"
#include "support/utility/null.h"
#include "support/utility/test.h"

static i32 test_memory_overlap() {
    i32  count = 0;
    char a[10] = {0};
    char b[10] = {0};

    SUPPORT_TEST_ASSERT(count,
                        memory_overlap(a, sizeof(a), b, sizeof(b)) == false);
    SUPPORT_TEST_ASSERT(count,
                        memory_overlap(a, sizeof(a), a, sizeof(a)) == true);
    SUPPORT_TEST_ASSERT(count,
                        memory_overlap(b, sizeof(b), b, sizeof(b)) == true);

    return count;
}

static i32 test_memory_set() {
    i32  count = 0;
    char a[10] = {0};

    {
        Result result = memory_set(a, sizeof(a), 5, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == 5);
        }
    }

    return count;
}

static i32 test_memory_copy() {
    i32  count = 0;
    char a[10] = {0};
    char b[10] = {0};

    {
        Result result = memory_set(a, sizeof(a), 5, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == 5);
        }
    }

    {
        Result result = memory_copy(a, b, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == b[i]);
        }
    }

    return count;
}

static i32 test_memory_move() {
    i32  count = 0;
    char a[10] = {0};
    char b[10] = {0};

    {
        Result result = memory_set(a, sizeof(a), 5, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == 5);
        }
    }

    {
        Result result = memory_move(a, b, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == b[i]);
        }
    }

    return count;
}

static i32 test_memory_compare() {
    i32  count = 0;
    char a[10] = {0};
    char b[10] = {0};

    {
        Result result = memory_set(a, sizeof(a), 5, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == 5);
        }
    }

    {
        Result result = memory_copy(a, b, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == b[i]);
        }
    }

    {
        i32    result = 0;
        Result res =
            memory_compare(a, sizeof(a), b, sizeof(b), sizeof(a), &result);
        SUPPORT_TEST_ASSERT(count, res == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count, result == 0);
    }

    return count;
}

static i32 test_memory_find() {
    i32  count = 0;
    char a[10] = {0};

    {
        Result result = memory_set(a, sizeof(a), 5, sizeof(a));
        SUPPORT_TEST_ASSERT(count, result == RESULT_SUCCESS);
        for (u64 i = 0; i < sizeof(a); ++i) {
            SUPPORT_TEST_ASSERT(count, a[i] == 5);
        }
    }

    {
        void  *result = NULL;
        Result res    = memory_find(a, sizeof(a), 5, &result);
        SUPPORT_TEST_ASSERT(count, res == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count, result == a);
    }

    {
        a[5]          = 'a';
        void  *result = NULL;
        Result res    = memory_find(a, sizeof(a), 'a', &result);
        SUPPORT_TEST_ASSERT(count, res == RESULT_SUCCESS);
        SUPPORT_TEST_ASSERT(count, result == a + 5);
        SUPPORT_TEST_ASSERT(count, *(char *)result == 'a');
    }

    return count;
}

i32 main([[maybe_unused]] i32 argc, [[maybe_unused]] char *argv[]) {
    i32 count = 0;

    count += test_memory_overlap();
    count += test_memory_set();
    count += test_memory_copy();
    count += test_memory_move();
    count += test_memory_compare();
    count += test_memory_find();

    return count;
}
