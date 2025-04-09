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
#include "support/types/result.h"
#include "support/types/scalar.h"
#include "support/utility/assert.h"

static Result
stream_open_imp(Stream *restrict stream, StringView path, StreamMode mode);
static Result stream_close_imp(Stream *restrict stream);
static Result stream_length_imp(Stream *restrict stream, u64 *length);
static Result
stream_write_imp(Stream *restrict stream, StringView view, i64 *bytes_written);
static Result stream_read_imp(Stream *restrict stream,
                              u8 *restrict buffer,
                              u64 buffer_size,
                              u64 bytes_requested,
                              i64 *restrict bytes_read);

Result stream_open(Stream *restrict stream, StringView path, StreamMode mode) {
    return stream_open_imp(stream, path, mode);
}

Result stream_close(Stream *restrict stream) {
    return stream_close_imp(stream);
}

Result stream_length(Stream *restrict stream, u64 *length) {
    return stream_length_imp(stream, length);
}

Result
stream_write(Stream *restrict stream, StringView view, i64 *bytes_written) {
    return stream_write_imp(stream, view, bytes_written);
}

Result stream_read(Stream *restrict stream,
                   u8  *buffer,
                   u64  buffer_size,
                   u64  bytes_requested,
                   i64 *bytes_read) {
    return stream_read_imp(
        stream, buffer, buffer_size, bytes_requested, bytes_read);
}

#if defined(SUPPORT_SYSTEM_HOST_OS_LINUX)
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

Stream stdin_stream_imp  = (Stream){STDIN_FILENO};
Stream stdout_stream_imp = (Stream){STDOUT_FILENO};
Stream stderr_stream_imp = (Stream){STDERR_FILENO};

Stream *stdin_stream  = &stdin_stream_imp;
Stream *stdout_stream = &stdout_stream_imp;
Stream *stderr_stream = &stderr_stream_imp;

static Result
stream_open_imp(Stream *restrict stream, StringView path, StreamMode mode) {
    if (stream == NULL) { return RESULT_NULL_TARGET; }
    {
        bool   empty  = false;
        Result result = string_view_empty(&path, &empty);
        if (result != RESULT_SUCCESS) { return result; }
        if (empty) { return RESULT_FILE_NOT_FOUND; }
    }

    i32 fd    = -1;
    i32 flags = 0;
    switch (mode) {
    case STREAM_MODE_READ:       flags = O_RDONLY; break;
    case STREAM_MODE_WRITE:      flags = O_WRONLY | O_CREAT; break;
    case STREAM_MODE_READ_WRITE: flags = O_RDWR | O_CREAT; break;
    default:                     return RESULT_INVALID_STREAM_MODE;
    }

    fd = open(path.data, flags);
    if (fd == -1) { return RESULT_ERRNO; }
    stream->file_descriptor = fd;
    return RESULT_SUCCESS;
}

static Result stream_close_imp(Stream *restrict stream) {
    if (stream == NULL) { return RESULT_NULL_SOURCE; }
    if (stream->file_descriptor == -1) { return RESULT_INVALID_STREAM; }

    i32 result = close(stream->file_descriptor);
    if (result == -1) { return RESULT_ERRNO; }
    stream->file_descriptor = -1;
    return RESULT_SUCCESS;
}

static Result stream_length_imp(Stream *restrict stream, u64 *length) {
    if (stream == NULL) { return RESULT_NULL_SOURCE; }
    if (length == NULL) { return RESULT_NULL_TARGET; }

    struct stat file_info;
    i32         result = fstat(stream->file_descriptor, &file_info);
    if (result == -1) { return RESULT_ERRNO; }

    *length = (u64)file_info.st_size;
    return RESULT_SUCCESS;
}

static Result
stream_write_imp(Stream *restrict stream, StringView view, i64 *bytes_written) {
    if (stream == NULL) { return RESULT_NULL_TARGET; }
    {
        bool   empty  = false;
        Result result = string_view_empty(&view, &empty);
        if (result != RESULT_SUCCESS) { return result; }
        if (empty) { return RESULT_SUCCESS; }
    }
    if (stream->file_descriptor == -1) { return RESULT_INVALID_STREAM; }

    *bytes_written = write(stream->file_descriptor, view.data, view.length);
    if (*bytes_written == -1) { return RESULT_ERRNO; }

    return RESULT_SUCCESS;
}

static Result stream_read_imp(Stream *restrict stream,
                              u8 *restrict buffer,
                              u64 buffer_size,
                              u64 bytes_requested,
                              i64 *restrict bytes_read) {
    if (stream == NULL) { return RESULT_NULL_TARGET; }
    if (buffer == NULL) { return RESULT_NULL_SOURCE; }
    if (bytes_read == NULL) { return RESULT_NULL_TARGET; }
    if (stream->file_descriptor == -1) { return RESULT_INVALID_STREAM; }
    if (buffer_size < bytes_requested) { return RESULT_UNDERSIZED_TARGET; }

    *bytes_read = read(stream->file_descriptor, buffer, bytes_requested);
    if (*bytes_read == -1) { return RESULT_ERRNO; }

    return RESULT_SUCCESS;
}

#else
#error "Unsupported Host OS " SUPPORT_SYSTEM_HOST_OS_NAME
#endif
