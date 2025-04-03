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
 * @file support/algorithm/memory.h
 * @brief memory manipulation functions.
 */

#ifndef EXP_SUPPORT_ALGORITHM_MEMORY_H
#define EXP_SUPPORT_ALGORITHM_MEMORY_H

#include "support/types/result.h"

/**
 * @brief Check if two memory regions overlap.
 */
bool memory_overlap(void const *a, u64 asize, void const *b, u64 bsize);

/**
 * @brief Set a block of memory to a specific value.
 *
 * @param target The target memory location.
 * @param size The size of the memory block.
 * @param value The value to set the memory to.
 * @param count The number of bytes to set.
 */
Result memory_set(void *restrict target, u64 size, char value, u64 count);

/**
 * @brief Copy a block of memory from one location to another.
 *
 * @warning If the source and target memory regions overlap, the behavior is
 * undefined. if either source or target is smaller than size, the behavior is
 * undefined.
 *
 * @param target The target memory location.
 * @param source The source memory.
 * @param size The number of bytes to copy.
 */
Result
memory_copy(void *restrict target, void const *restrict source, u64 size);

/**
 * @brief Move a block of memory from one location to another.
 *
 * This function is similar to `memory_copy`, but it handles overlapping
 * memory regions correctly.
 */
Result memory_move(void *target, void const *source, u64 size);

/**
 * @brief Compare lexicographically two blocks of memory.
 */
Result memory_compare(
    void const *a, u64 asize, void const *b, u64 bsize, u64 count, i32 *result);

/**
 * @brief Find the first occurrence of a value in a block of memory.
 */
Result
memory_find(void const *restrict target, u64 size, char value, void **result);

#endif // !EXP_SUPPORT_ALGORITHM_MEMORY_H
