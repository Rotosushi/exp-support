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

#include "support/types/stream.h"
#include "support/system/host.h"

static Result stream_open_imp(Stream *stream, StringView path, StreamMode mode);
static Result stream_close_imp(Stream stream);
static Result stream_length_imp(Stream stream, u64 *length);
static Result stream_write_imp(Stream stream, StringView view);
static Result
stream_read_imp(Stream stream, void *buffer, u64 size, u64 *bytes_read);

Result stream_open(Stream *stream, StringView path, StreamMode mode) {
    return stream_open_imp(stream, path, mode);
}

Result stream_close(Stream stream) { return stream_close_imp(stream); }

Result stream_length(Stream stream, u64 *length) {
    return stream_length_imp(stream, length);
}

Result stream_write(Stream stream, StringView view) {
    return stream_write_imp(stream, view);
}

Result stream_read(Stream stream, void *buffer, u64 size, u64 *bytes_read) {
    return stream_read_imp(stream, buffer, size, bytes_read);
}

#if defined(SUPPORT_SYSTEM_HOST_LINUX)
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Stream_ {
    int fd;
} Stream_;

Stream_ stdin_stream_imp  = (Stream_){STDIN_FILENO};
Stream_ stdout_stream_imp = (Stream_){STDOUT_FILENO};
Stream_ stderr_stream_imp = (Stream_){STDERR_FILENO};

Stream stdin_stream  = &stdin_stream_imp;
Stream stdout_stream = &stdout_stream_imp;
Stream stderr_stream = &stderr_stream_imp;

static Result
stream_open_imp(Stream *stream, StringView path, StreamMode mode) {
    int fd    = -1;
    int flags = 0;
    switch (mode) {
    case STREAM_MODE_READ:       flags = O_RDONLY; break;
    case STREAM_MODE_WRITE:      flags = O_WRONLY | O_CREAT | O_TRUNC; break;
    case STREAM_MODE_READ_WRITE: flags = O_RDWR | O_CREAT | O_TRUNC; break;
    default:                     return RESULT_INVALID_STREAM_MODE;
    }

    fd = open(path.data, flags);
}

static Result stream_close_imp(Stream stream);
static Result stream_length_imp(Stream stream, u64 *length);
static Result stream_write_imp(Stream stream, StringView view);
static Result
stream_read_imp(Stream stream, void *buffer, u64 size, u64 *bytes_read);

#else
#error "Unsupported Host OS " SUPPORT_SYSTEM_HOST_OS_NAME
#endif
