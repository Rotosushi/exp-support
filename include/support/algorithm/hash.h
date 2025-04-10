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
 * @file support/algorithm/hash.h
 * @brief hash functions.
 */

#ifndef SUPPORT_ALGORITHM_HASH_H
#define SUPPORT_ALGORITHM_HASH_H

#include "support/types/result.h"
#include "support/types/scalar.h"

/**
 * @brief Hashes a buffer using the djb2 algorithm.
 *
 * @note http://www.cse.yorku.ca/~oz/hash.html
 *
 */
Result
hash_djb2(u8 const *restrict buffer, u64 buffer_length, u64 *restrict hash);

/**
 * @brief Hashes a buffer using the sdbm algorithm.
 *
 * @note http://www.cse.yorku.ca/~oz/hash.html
 *
 */
Result
hash_sdbm(u8 const *restrict buffer, u64 buffer_length, u64 *restrict hash);

/**
 * @brief Hashes a buffer using the FNV-1a algorithm.
 *
 * @note https://github.com/lcn2/fnv/blob/master/hash_64a.c
 *
 */
Result
hash_fnv1a(u8 const *restrict buffer, u64 buffer_length, u64 *restrict hash);

#endif // !SUPPORT_ALGORITHM_HASH_H
