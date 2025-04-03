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

#include "support/types/scalar.h"

typedef struct StringView {
    u64         length;
    char const *data;
} StringView;

inline StringView string_view(u64 length, char const *data) {
    return (StringView){length, data};
}

#define SV(s) (string_view(sizeof(s) - 1, (s)))

#endif // !SUPPORT_TYPES_STRING_VIEW_H
