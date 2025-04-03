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
 * @file support/utility/assert.h
 * @brief assert macros for debugging.
 */

#ifndef SUPPORT_UTILITY_ASSERT_H
#define SUPPORT_UTILITY_ASSERT_H

#include "support/utility/panic.h"

#if defined(SUPPORT_REMOVE_ASSERTS)
#define assert(condition) ((void)0)
#else
#define assert(condition)                                                      \
    ((condition) || (PANIC("assertion failed: " #condition), 0))
#endif // SUPPORT_REMOVE_ASSERTS

#if defined(SUPPORT_REMOVE_ASSERTS) || defined(NDEBUG)
#define assert_debug(condition) ((void)0)
#else
#define assert_debug(condition)                                                \
    ((condition) || (PANIC("assertion failed: " #condition), 0))
#endif // SUPPORT_REMOVE_ASSERTS || NDEBUG

#define assert_always(condition)                                               \
    ((condition) || (PANIC("assertion failed: " #condition), 0))

#endif // !SUPPORT_UTILITY_ASSERT_H
