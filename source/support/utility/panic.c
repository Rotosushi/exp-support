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

#include "support/algorithm/memory.h"
#include "support/utility/message.h"
#include "support/utility/panic.h"

[[noreturn]] void panic(StringView msg, StringView file, i32 line) {
    MessageInfo message_info = {
        .type    = MESSAGE_TYPE_FATAL,
        .line    = line,
        .file    = file,
        .message = msg,
    };
    message(&message_info, stderr_stream);
    abort();
}

[[noreturn]] void
panic_result(Result result, StringView msg, StringView file, i32 line) {
    StringView result_string_view;
    result_to_string_view(&result_string_view, result);

    StringView text = SV(": ");
    char       buffer[result_string_view.length + text.length + msg.length + 1];
    if (memory_copy(buffer,
                    result_string_view.data,
                    result_string_view.length) != RESULT_SUCCESS) {
        abort();
    }
    if (memory_copy(buffer + result_string_view.length,
                    text.data,
                    text.length) != RESULT_SUCCESS) {
        abort();
    }
    if (memory_copy(buffer + result_string_view.length + text.length,
                    msg.data,
                    msg.length) != RESULT_SUCCESS) {
        abort();
    }
    buffer[result_string_view.length + text.length + msg.length] = '\0';

    MessageInfo message_info = {
        .type    = MESSAGE_TYPE_FATAL,
        .line    = line,
        .file    = file,
        .message = string_view(result_string_view.length + msg.length, buffer),
    };
    message(&message_info, stderr_stream);
    abort();
}
