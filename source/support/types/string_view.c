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
 * @file support/types/string_view.h
 * @brief a constant view into a block of memory.
 */

#include "support/types/string_view.h"
#include "support/algorithm/cstring.h"
#include "support/algorithm/memory.h"
#include "support/utility/null.h"

extern StringView string_view(u64 length, char const *restrict data);

Result string_view_from_cstring(StringView *restrict view,
                                char const *restrict cstring) {
    if (cstring == NULL) { return RESULT_NULL_SOURCE; }
    if (view == NULL) { return RESULT_NULL_TARGET; }
    if (view->data == NULL) { return RESULT_STRING_VIEW_NULL_DATA; }

    u64    length = 0;
    Result result = cstring_length(cstring, &length);
    if (result != RESULT_SUCCESS) { return result; }

    *view = string_view(length, cstring);
    return RESULT_SUCCESS;
}

Result string_view_compare(StringView const *restrict a,
                           StringView const *restrict b,
                           i32 *restrict result) {
    if (a == NULL) { return RESULT_NULL_SOURCE; }
    if (a->data == NULL) { return RESULT_STRING_VIEW_NULL_DATA; }
    if (b == NULL) { return RESULT_NULL_SOURCE; }
    if (b->data == NULL) { return RESULT_STRING_VIEW_NULL_DATA; }
    if (result == NULL) { return RESULT_NULL_TARGET; }
    if (a->length == 0 && b->length == 0) {
        *result = 0;
        return RESULT_SUCCESS;
    }

    i32    difference = 0;
    Result cmp_result =
        memory_compare(a->data,
                       a->length,
                       b->data,
                       b->length,
                       a->length < b->length ? a->length : b->length,
                       &difference);
    if (result != RESULT_SUCCESS) { return cmp_result; }

    *result = difference;
    return RESULT_SUCCESS;
}

Result string_view_empty(StringView const *restrict view,
                         bool *restrict result) {
    if (view == NULL) { return RESULT_NULL_SOURCE; }
    if (view->data == NULL) { return RESULT_STRING_VIEW_NULL_DATA; }
    if (result == NULL) { return RESULT_NULL_TARGET; }

    *result = (view->length == 0);
    return RESULT_SUCCESS;
}
