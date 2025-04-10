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
 * @file support/utility/unreachable.c
 * @brief a macro for unreachable.
 */

#ifndef SUPPORT_UTILITY_UNREACHABLE_H
#define SUPPORT_UTILITY_UNREACHABLE_H

#include "support/utility/panic.h"

#if !defined(NDEBUG)
#define SUPPORT_UNREACHABLE() PANIC("unreachable code reached");
#else
#include <stddef.h>
#define SUPPORT_UNREACHABLE() unreachable()
#endif // !NDEBUG

#endif // !SUPPORT_UTILITY_UNREACHABLE_H
