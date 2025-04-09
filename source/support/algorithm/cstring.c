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
 * @file support/algorithm/cstring.c
 * @brief C-string utility functions.
 */

#include "support/algorithm/cstring.h"
#include "support/algorithm/memory.h"
#include "support/utility/null.h"
#include "support/utility/numbers.h"

#define CSTRING_MAX_LENGTH (8 * SUPPORT_KIBIBYTE)

Result cstring_length(const char *restrict cstring, u64 *length) {
    if (cstring == NULL) { return RESULT_NULL_SOURCE; }
    if (length == NULL) { return RESULT_NULL_TARGET; }

    u8    *null_terminator = NULL;
    Result result          = memory_find(
        cstring, CSTRING_MAX_LENGTH, '\0', (void **)(&null_terminator));
    if (result != RESULT_SUCCESS) { return result; }
    if (null_terminator == NULL) { return RESULT_CSTRING_EXCEEDS_MAX_LENGTH; }

    *length = (u64)(null_terminator - (u8 *)cstring);
    return RESULT_SUCCESS;
}
