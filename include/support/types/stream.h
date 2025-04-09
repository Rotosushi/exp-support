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

#include "support/system/host.h"
#include "support/types/result.h"
#include "support/types/scalar.h"
#include "support/types/string_view.h"

#if defined(SUPPORT_SYSTEM_HOST_OS_LINUX)
typedef struct Stream {
    i32 file_descriptor;
} Stream;
#elif defined(SUPPORT_SYSTEM_HOST_OS_WINDOWS)
typedef struct Stream {
    void *handle;
} Stream;
#else
#error "Unsupported platform: " SUPPORT_SYSTEM_HOST_OS_NAME
#endif

extern Stream *stdin_stream;
extern Stream *stdout_stream;
extern Stream *stderr_stream;

typedef enum StreamMode {
    STREAM_MODE_READ,
    STREAM_MODE_WRITE,
    STREAM_MODE_READ_WRITE,
} StreamMode;

Result stream_open(Stream *restrict stream, StringView path, StreamMode mode);
Result stream_close(Stream *restrict stream);
Result stream_length(Stream *restrict stream, u64 *length);
Result
stream_write(Stream *restrict stream, StringView view, i64 *bytes_written);
Result stream_read(Stream *restrict stream,
                   u8 *restrict buffer,
                   u64 buffer_size,
                   u64 bytes_requested,
                   i64 *restrict bytes_read);

#endif // !SUPPORT_TYPES_STREAM_H
