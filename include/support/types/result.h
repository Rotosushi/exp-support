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
 * @file support/types/result.h
 * @brief a result type for functions that can fail.
 */

#ifndef SUPPORT_TYPES_RESULT_H
#define SUPPORT_TYPES_RESULT_H

typedef enum Result {
    RESULT_SUCCESS,
    RESULT_FAILURE,
    RESULT_ERRNO,
    RESULT_INTEGER_OVERFLOW,
    RESULT_INVALID_ARGUMENT,
    RESULT_NULL_TARGET,
    RESULT_NULL_SOURCE,
    RESULT_UNDERSIZED_TARGET,
    RESULT_UNDERSIZED_SOURCE,
    RESULT_TARGET_SOURCE_OVERLAP,
    RESULT_CSTRING_EXCEEDS_MAX_LENGTH,
    RESULT_STRING_VIEW_NULL_DATA,
    RESULT_INVALID_STREAM,
    RESULT_INVALID_STREAM_MODE,
    RESULT_FILE_NOT_FOUND,
} Result;

struct StringView;
void result_to_string_view(struct StringView *restrict view, Result result);

#endif // !SUPPORT_TYPES_RESULT_H
