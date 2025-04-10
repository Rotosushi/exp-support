// Copyright (C) 2025 cade-weinberg
//
// This file is part of support.
//
// support is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// support is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with support.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @file support/algorithm/malloc.h
 * @brief malloc wrapper functions.
 */

#ifndef SUPPORT_ALGORITHM_MALLOC_H
#define SUPPORT_ALGORITHM_MALLOC_H

#include "support/types/result.h"
#include "support/types/scalar.h"

Result support_malloc(void **restrict ptr, u64 size);
Result support_calloc(void **restrict ptr, u64 count, u64 size);
Result support_realloc(void **restrict ptr, u64 size);
Result support_free(void *restrict ptr);

#endif // !SUPPORT_ALGORITHM_MALLOC_H
