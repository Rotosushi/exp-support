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
 * @file support/utility/break.h
 * @brief a macro for inserting a breakpoint.
 */

#ifndef SUPPORT_UTILITY_BREAK_H
#define SUPPORT_UTILITY_BREAK_H

#include "support/system/host.h"

#if defined(SUPPORT_SYSTEM_HOST_COMPILER_GCC) ||                               \
    defined(SUPPORT_SYSTEM_HOST_COMPILER_CLANG)
#define SUPPORT_BREAK() __builtin_trap()
#elif defined(SUPPORT_SYSTEM_HOST_COMPILER_MSVC)
#define SUPPORT_BREAK() __debugbreak()
#else
#include <stdlib.h>
#define SUPPORT_BREAK() abort()
#endif // !defined(SUPPORT_SYSTEM_HOST_COMPILER_GCC) ||
       // defined(SUPPORT_SYSTEM_HOST_COMPILER_CLANG)

#endif // !SUPPORT_UTILITY_BREAK_H
