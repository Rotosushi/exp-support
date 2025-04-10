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

#include "support/types/result.h"
#include "support/types/string_view.h"
#include "support/utility/assert.h"
#include "support/utility/null.h"

void result_to_string_view(StringView *restrict view, Result result) {
    assert(view != NULL);
    switch (result) {
    case RESULT_SUCCESS:           *view = SV("success"); break;
    case RESULT_FAILURE:           *view = SV("failure"); break;
    case RESULT_ERRNO:             *view = SV("errno"); break;
    case RESULT_NULL_TARGET:       *view = SV("null target"); break;
    case RESULT_NULL_SOURCE:       *view = SV("null source"); break;
    case RESULT_UNDERSIZED_TARGET: *view = SV("undersized target"); break;
    case RESULT_UNDERSIZED_SOURCE: *view = SV("undersized source"); break;
    case RESULT_TARGET_SOURCE_OVERLAP:
        *view = SV("target and source overlap");
        break;
    case RESULT_CSTRING_EXCEEDS_MAX_LENGTH:
        *view = SV("cstring exceeds max length");
        break;
    case RESULT_STRING_VIEW_NULL_DATA:
        *view = SV("string view null data");
        break;
    case RESULT_INVALID_STREAM:      *view = SV("invalid stream"); break;
    case RESULT_INVALID_STREAM_MODE: *view = SV("invalid stream mode"); break;
    case RESULT_FILE_NOT_FOUND:      *view = SV("file not found"); break;
    default:                         {
        *view = SV("unknown result");
        break;
    }
    }
}
