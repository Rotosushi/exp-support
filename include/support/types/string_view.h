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
 * @file support/types/string_view.h
 * @brief a constant view into a block of memory.
 */

#ifndef SUPPORT_TYPES_STRING_VIEW_H
#define SUPPORT_TYPES_STRING_VIEW_H

#include "support/types/result.h"
#include "support/types/scalar.h"

/**
 * @brief A constant view into a sequence of characters.
 *
 * @warning the StringView struct does not own the data it points to.
 *          The data must remain valid for the lifetime of the StringView.
 *
 */
typedef struct StringView {
    u64         length;
    char const *data;
} StringView;

/**
 * @brief Create a StringView from a length and a pointer to data.
 */
inline StringView string_view(u64 length, char const *restrict data) {
    return (StringView){length, data};
}

/**
 * @brief Create a StringView from a C-string.
 */
Result string_view_from_cstring(StringView *restrict view,
                                char const *restrict cstring);

/**
 * @brief Compare two StringViews lexicographically.
 */
Result string_view_compare(StringView const *restrict a,
                           StringView const *restrict b,
                           i32 *restrict result);

/**
 * @brief Check if a StringView is empty.
 */
Result string_view_empty(StringView const *restrict view,
                         bool *restrict result);

/**
 * @def SV
 * @brief Create a StringView from a string literal.
 *
 * @note I think this macro would also work if given a null-terminated char
 * array. however one must be careful to ensure the lifetime of the array is
 * longer than the StringView.
 *
 * @warning this macro will not work if given a char pointer. use
 * string_view_from_cstring instead.
 */
#define SV(s) (string_view(sizeof(s) - 1, (s)))

#endif // !SUPPORT_TYPES_STRING_VIEW_H
