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
 * @file support/utility/panic.h
 * @brief panic macros for debugging.
 */

#ifndef SUPPORT_UTILITY_PANIC_H
#define SUPPORT_UTILITY_PANIC_H

#include "support/types/result.h"
#include "support/types/string_view.h"

[[noreturn]] void panic(StringView message, StringView file, i32 line);
[[noreturn]] void
panic_result(Result result, StringView message, StringView file, i32 line);

#define PANIC(message) panic(SV(message), SV(__FILE__), __LINE__)
#define PANIC_RESULT(result, message)                                          \
    panic_result(result, SV(message), SV(__FILE__), __LINE__)

#endif // !SUPPORT_UTILITY_PANIC_H
