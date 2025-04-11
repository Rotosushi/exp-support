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
#include <stdlib.h>

#include "support/algorithm/allocate.h"
#include "support/system/host.h"
#include "support/types/result.h"
#include "support/utility/null.h"

#define GROWTH_FACTOR 2

Result grow_dynamic_array(void **restrict array,
                          u64 *restrict capacity,
                          u64 element_size) {
    if (array == NULL || capacity == NULL) { return RESULT_NULL_SOURCE; }
    if (element_size == 0) { return RESULT_INVALID_ARGUMENT; }
    if (*capacity == 0) { *capacity = 1; }

#if defined(SUPPORT_SYSTEM_HOST_COMPILER_GCC) ||                               \
    defined(SUPPORT_SYSTEM_HOST_COMPILER_CLANG)
    if (__builtin_mul_overflow(*capacity, GROWTH_FACTOR, capacity)) {
        return RESULT_INTEGER_OVERFLOW;
    }

    u64 alloc_size = 0;
    if (__builtin_mul_overflow(*capacity, element_size, &alloc_size)) {
        return RESULT_INTEGER_OVERFLOW;
    }
#else
    u64 new_capacity = *capacity * GROWTH_FACTOR;
    if (new_capacity / *capacity != GROWTH_FACTOR) {
        return RESULT_INTEGER_OVERFLOW;
    }
    *capacity = new_capacity;

    u64 alloc_size = *capacity * element_size;
    if (alloc_size / *capacity != element_size) {
        return RESULT_INTEGER_OVERFLOW;
    }
#endif

    void *buffer = realloc(*array, alloc_size);
    if (buffer == NULL) { return RESULT_ERRNO; }

    *array = buffer;
    return RESULT_SUCCESS;
}
