/**
 * Copyright (C) 2025 Cade Weinberg
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

#include "support/algorithm/conversion.h"
#include "support/utility/null.h"

u64 convert_base_10_u64_buffer_length(u64 value) {
    if (value < 10) return 1;
    if (value < 100) return 2;
    if (value < 1'000) return 3;
    if (value < 10'000) return 4;
    if (value < 100'000) return 5;
    if (value < 1'000'000) return 6;
    if (value < 10'000'000) return 7;
    if (value < 100'000'000) return 8;
    if (value < 1'000'000'000) return 9;
    if (value < 10'000'000'000) return 10;
    if (value < 100'000'000'000) return 11;
    if (value < 1'000'000'000'000) return 12;
    if (value < 10'000'000'000'000) return 13;
    if (value < 100'000'000'000'000) return 14;
    if (value < 1'000'000'000'000'000) return 15;
    if (value < 10'000'000'000'000'000) return 16;
    if (value < 100'000'000'000'000'000) return 17;
    if (value < 1'000'000'000'000'000'000) return 18;
    if (value < 10'000'000'000'000'000'000ULL) return 19;
    return 20;
}

Result
convert_base_10_u64(u64 value, char *restrict buffer, u64 buffer_length) {
    if (buffer == NULL) { return RESULT_NULL_TARGET; }
    if (buffer_length < convert_base_10_u64_buffer_length(value)) {
        return RESULT_UNDERSIZED_TARGET;
    }

    char *ptr1, *ptr2;
    char mapping[] = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijkl"
                     "mnopqrstuvwxyz";

    // convert the number
    ptr1 = buffer;
    do {
        u64 tmp = value;
        value /= 10;
        *ptr1++ = mapping[35 + (tmp - value * 10)];
    } while (value);

    // append the null terminator
    ptr2    = buffer;
    buffer  = ptr1;
    *ptr1-- = '\0';

    // reverse the string
    while (ptr2 < ptr1) {
        char tmp = *ptr1;
        *ptr1--  = *ptr2;
        *ptr2++  = tmp;
    }

    return RESULT_SUCCESS;
}

u64 convert_base_10_i64_buffer_length(i64 value) {
    if (value < 0) {
        value = (value == i64_MIN) ? i64_MAX : -value;
        return 1 + convert_base_10_u64_buffer_length((u64)value);
    }
    return convert_base_10_u64_buffer_length((u64)value);
}

Result
convert_base_10_i64(i64 value, char *restrict buffer, u64 buffer_length) {
    if (buffer == NULL) { return RESULT_NULL_TARGET; }
    if (buffer_length < convert_base_10_i64_buffer_length(value)) {
        return RESULT_UNDERSIZED_TARGET;
    }

    i64   tmp_value;
    char *ptr1, *ptr2;
    char mapping[] = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijkl"
                     "mnopqrstuvwxyz";

    // convert the number
    ptr1 = buffer;
    do {
        tmp_value = value;
        value /= 10;
        *ptr1++ = mapping[35 + (tmp_value - value * 10)];
    } while (value);

    // append the sign
    if (tmp_value < 0) { *ptr1++ = '-'; }
    // null terminate
    ptr2    = buffer;
    buffer  = ptr1;
    *ptr1-- = '\0';

    // reverse the string
    while (ptr2 < ptr1) {
        char tmp = *ptr1;
        *ptr1--  = *ptr2;
        *ptr2++  = tmp;
    }

    return RESULT_SUCCESS;
}
