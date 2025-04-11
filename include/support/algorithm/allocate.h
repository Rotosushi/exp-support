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
 * @file support/algorithm/allocate.h
 * @brief memory allocation helpers.
 */

#ifndef SUPPORT_ALGORITHM_ALLOCATE_H
#define SUPPORT_ALGORITHM_ALLOCATE_H

#include "support/types/result.h"
#include "support/types/scalar.h"

/**
 * @brief Grows a dynamic array by a factor of 2.
 *
 * @param array     Pointer to the array to grow.
 * @param capacity  Pointer to the current capacity of the array.
 * @param element_size Size of each element in the array.
 * @return RESULT_SUCCESS on success, or an error code on failure.
 */
Result grow_dynamic_array(void **restrict array,
                          u64 *restrict capacity,
                          u64 element_size);

#endif // !SUPPORT_ALGORITHM_ALLOCATE_H
