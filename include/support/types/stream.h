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
 * @file support/types/stream.h
 * @brief input/output streams.
 */

#ifndef SUPPORT_TYPES_STREAM_H
#define SUPPORT_TYPES_STREAM_H

#include "support/types/result.h"
#include "support/types/string_view.h"

struct Stream_;
typedef struct Stream_ *Stream;

Result stream_open(Stream *stream, StringView path, StringView mode);
Result stream_close(Stream stream);
Result stream_length(Stream stream, u64 *length);
Result stream_write(Stream stream, StringView view);
Result stream_read(Stream stream, void *buffer, u64 size, u64 *bytes_read);

#endif // !SUPPORT_TYPES_STREAM_H
