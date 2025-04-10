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

#include <stdlib.h>

#include "support/algorithm/conversion.h"
#include "support/algorithm/memory.h"
#include "support/utility/ansi_color_codes.h"
#include "support/utility/assert.h"
#include "support/utility/message.h"
#include "support/utility/unreachable.h"

#define SUPPORT_MESSAGE_INFO    (ANSI_COLOR_BLUE "INFO" ANSI_COLOR_RESET)
#define SUPPORT_MESSAGE_TRACE   (ANSI_COLOR_CYAN "TRACE" ANSI_COLOR_RESET)
#define SUPPORT_MESSAGE_DEBUG   (ANSI_COLOR_GREEN "DEBUG" ANSI_COLOR_RESET)
#define SUPPORT_MESSAGE_WARNING (ANSI_COLOR_YELLOW "WARNING" ANSI_COLOR_RESET)
#define SUPPORT_MESSAGE_ERROR   (ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET)
#define SUPPORT_MESSAGE_FATAL                                                  \
    (ANSI_COLOR_RED ANSI_COLOR_BOLD "FATAL" ANSI_COLOR_RESET)

static StringView message_type_to_view(MessageType type) {
    switch (type) {
    case MESSAGE_TYPE_INFO:    return SV(SUPPORT_MESSAGE_INFO);
    case MESSAGE_TYPE_TRACE:   return SV(SUPPORT_MESSAGE_TRACE);
    case MESSAGE_TYPE_DEBUG:   return SV(SUPPORT_MESSAGE_DEBUG);
    case MESSAGE_TYPE_WARNING: return SV(SUPPORT_MESSAGE_WARNING);
    case MESSAGE_TYPE_ERROR:   return SV(SUPPORT_MESSAGE_ERROR);
    case MESSAGE_TYPE_FATAL:   return SV(SUPPORT_MESSAGE_FATAL);
    default:                   SUPPORT_UNREACHABLE();
    }
}

static void message_with_file(MessageInfo const *restrict message_info,
                              Stream *restrict stream);

static void message_without_file(MessageInfo const *restrict message_info,
                                 Stream *restrict stream);

void message(MessageInfo const *restrict message_info,
             Stream *restrict stream) {
    assert(message_info != NULL);
    assert(stream != NULL);

    bool   empty  = false;
    Result result = string_view_is_empty(&message_info->file, &empty);
    if (result != RESULT_SUCCESS) {
        PANIC_RESULT(result, "string_view_empty failed");
    }

    if (empty) {
        message_without_file(message_info, stream);
    } else {
        message_with_file(message_info, stream);
    }
}

static void message_with_file(MessageInfo const *restrict message_info,
                              Stream *restrict stream) {
    StringView t0 = SV("["), t1 = SV(" @ "), t2 = SV(":"), t3 = SV("] "),
               t4           = SV("\n");
    StringView message_type = message_type_to_view(message_info->type);
    u64        line_buffer_length =
        convert_base_10_i64_buffer_length(message_info->line);
    char line_buffer[line_buffer_length + 1];
    {
        Result result = convert_base_10_i64(
            message_info->line, line_buffer, line_buffer_length);
        if (result != RESULT_SUCCESS) {
            PANIC_RESULT(result, "convert_base_10_u64 failed");
        }
    }
    StringView line = string_view(line_buffer_length, line_buffer);

    u64 message_length = t0.length + message_type.length + t1.length +
                         message_info->file.length + t2.length + line.length +
                         t3.length + message_info->message.length + t4.length;
    char message_buffer[message_length + 1];
    u64  offset = 0;
    if (memory_copy(message_buffer + offset, t0.data, t0.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t0.length;
    if (memory_copy(message_buffer + offset,
                    message_type.data,
                    message_type.length) != RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += message_type.length;
    if (memory_copy(message_buffer + offset, t1.data, t1.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t1.length;
    if (memory_copy(message_buffer + offset,
                    message_info->file.data,
                    message_info->file.length) != RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += message_info->file.length;
    if (memory_copy(message_buffer + offset, t2.data, t2.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t2.length;
    if (memory_copy(message_buffer + offset, line.data, line.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += line.length;
    if (memory_copy(message_buffer + offset, t3.data, t3.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t3.length;
    if (memory_copy(message_buffer + offset,
                    message_info->message.data,
                    message_info->message.length) != RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += message_info->message.length;
    if (memory_copy(message_buffer + offset, t4.data, t4.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t4.length;
    message_buffer[message_length] = '\0';
    i64 bytes_written              = 0;
    offset                         = 0;
    do {
        StringView view =
            string_view(message_length - offset, message_buffer + offset);
        Result result = stream_write(stream, view, &bytes_written);
        if (result != RESULT_SUCCESS) {
            PANIC_RESULT(result, "stream_write failed");
        }
        offset += (u64)bytes_written;
    } while ((u64)bytes_written != message_length);
}

static void message_without_file(MessageInfo const *restrict message_info,
                                 Stream *restrict stream) {
    StringView t0 = SV("["), t1 = SV("]"), t2 = SV("\n");
    StringView message_type = message_type_to_view(message_info->type);

    u64 message_length = t0.length + message_type.length + t1.length +
                         message_info->message.length + t2.length;
    char message_buffer[message_length + 1];
    u64  offset = 0;
    if (memory_copy(message_buffer + offset, t0.data, t0.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t0.length;
    if (memory_copy(message_buffer + offset,
                    message_type.data,
                    message_type.length) != RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += message_type.length;
    if (memory_copy(message_buffer + offset, t1.data, t1.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t1.length;
    if (memory_copy(message_buffer + offset,
                    message_info->message.data,
                    message_info->message.length) != RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += message_info->message.length;
    if (memory_copy(message_buffer + offset, t2.data, t2.length) !=
        RESULT_SUCCESS) {
        PANIC_RESULT(RESULT_ERRNO, "memory_copy failed");
    }
    offset += t2.length;
    message_buffer[message_length] = '\0';
    i64 bytes_written              = 0;
    offset                         = 0;
    do {
        StringView view =
            string_view(message_length - offset, message_buffer + offset);
        Result result = stream_write(stream, view, &bytes_written);
        if (result != RESULT_SUCCESS) {
            PANIC_RESULT(result, "stream_write failed");
        }
        offset += (u64)bytes_written;
    } while ((u64)bytes_written != message_length);
}
