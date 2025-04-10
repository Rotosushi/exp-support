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

#include "support/algorithm/hash.h"
#include "support/utility/null.h"

Result
hash_djb2(u8 const *restrict buffer, u64 buffer_length, u64 *restrict hash) {
    if (buffer == NULL) { return RESULT_NULL_SOURCE; }
    if (hash == NULL) { return RESULT_NULL_TARGET; }

    u64 hash_value = 5381;
    for (u64 i = 0; i < buffer_length; ++i) {
        hash_value = ((hash_value << 5) + hash_value) + buffer[i];
    }

    *hash = hash_value;
    return RESULT_SUCCESS;
}

Result
hash_sdbm(u8 const *restrict buffer, u64 buffer_length, u64 *restrict hash) {
    if (buffer == NULL) { return RESULT_NULL_SOURCE; }
    if (hash == NULL) { return RESULT_NULL_TARGET; }

    u64 hash_value = 0;
    for (u64 i = 0; i < buffer_length; ++i) {
        hash_value =
            buffer[i] + (hash_value << 6) + (hash_value << 16) - hash_value;
    }

    *hash = hash_value;
    return RESULT_SUCCESS;
}

Result
hash_fnv1a(u8 const *restrict buffer, u64 buffer_length, u64 *restrict hash) {
    if (buffer == NULL) { return RESULT_NULL_SOURCE; }
    if (hash == NULL) { return RESULT_NULL_TARGET; }

    u64 hash_value = 14695981039346656037ULL;
    for (u64 i = 0; i < buffer_length; ++i) {
        hash_value ^= buffer[i];
        hash_value *= 1099511628211ULL;
    }

    *hash = hash_value;
    return RESULT_SUCCESS;
}
