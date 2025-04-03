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

#include "support/algorithm/memory.h"
#include "support/types/result.h"

bool memory_overlap(void const *a, u64 asize, void const *b, u64 bsize) {
    if (a == 0 || b == 0) { return false; }
    if (asize == 0 || bsize == 0) { return false; }

    char const *a_ptr = (char const *)a;
    char const *b_ptr = (char const *)b;

    return (a_ptr < (b_ptr + bsize) && b_ptr < (a_ptr + asize));
}

Result memory_set(void *restrict target, u64 size, char value, u64 count) {
    if (target == 0) { return RESULT_NULL_TARGET; }
    if (size < count) { return RESULT_UNDERSIZED_TARGET; }
    if (count == 0) { return RESULT_SUCCESS; }

    char *target_ptr = (char *)target;
    for (u64 index = 0; index < count; ++index) {
        target_ptr[index] = value;
    }
    return RESULT_SUCCESS;
}

Result
memory_copy(void *restrict target, void const *restrict source, u64 size) {
    if (target == 0) { return RESULT_NULL_TARGET; }
    if (source == 0) { return RESULT_NULL_SOURCE; }
    if (size == 0) { return RESULT_SUCCESS; }
    if (memory_overlap(target, size, source, size)) {
        return RESULT_TARGET_SOURCE_OVERLAP;
    }

    char       *target_ptr = (char *)target;
    char const *source_ptr = (char const *)source;
    for (u64 index = 0; index < size; ++index) {
        target_ptr[index] = source_ptr[index];
    }
    return RESULT_SUCCESS;
}

Result
memory_move(void *restrict target, void const *restrict source, u64 size) {
    if (target == 0) { return RESULT_NULL_TARGET; }
    if (source == 0) { return RESULT_NULL_SOURCE; }
    if (size == 0) { return RESULT_SUCCESS; }

    char       *target_ptr = (char *)target;
    char const *source_ptr = (char const *)source;
    if (memory_overlap(target, size, source, size)) {
        for (u64 index = size; index > 0; --index) {
            target_ptr[index - 1] = source_ptr[index - 1];
        }
        return RESULT_SUCCESS;
    }

    for (u64 index = 0; index < size; ++index) {
        target_ptr[index] = source_ptr[index];
    }

    return RESULT_SUCCESS;
}

Result memory_compare(const void *a,
                      u64         asize,
                      const void *b,
                      u64         bsize,
                      u64         count,
                      i32        *result) {
    if (a == 0) { return RESULT_NULL_SOURCE; }
    if (b == 0) { return RESULT_NULL_SOURCE; }
    if (asize < count) { return RESULT_UNDERSIZED_SOURCE; }
    if (bsize < count) { return RESULT_UNDERSIZED_SOURCE; }
    if (count == 0) {
        *result = 0;
        return RESULT_SUCCESS;
    }

    char const *a_ptr = (char const *)a;
    char const *b_ptr = (char const *)b;

    for (u64 index = 0; index < count; ++index) {
        if (a_ptr[index] != b_ptr[index]) {
            *result = a_ptr[index] - b_ptr[index];
            return RESULT_SUCCESS;
        }
    }

    *result = 0;
    return RESULT_SUCCESS;
}

Result
memory_find(const void *restrict source, u64 size, char value, void **result) {
    if (source == 0) { return RESULT_NULL_SOURCE; }
    if (size == 0) { return RESULT_UNDERSIZED_SOURCE; }
    if (result == 0) { return RESULT_NULL_TARGET; }

    char const *source_ptr = (char const *)source;
    for (u64 index = 0; index < size; ++index) {
        if (source_ptr[index] == value) {
            *result = (void *)(source_ptr + index);
            return RESULT_SUCCESS;
        }
    }

    *result = 0;
    return RESULT_SUCCESS;
}
