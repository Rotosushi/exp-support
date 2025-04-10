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
 * @file support/algorithm/random.h
 * @brief pseudo random number generation functions.
 */

#ifndef SUPPORT_ALGORITHM_RANDOM_H
#define SUPPORT_ALGORITHM_RANDOM_H

#include "support/types/result.h"
#include "support/types/scalar.h"

/**
 * @brief SplitMix64 pseudo random number generator.
 *
 * @note https://en.wikipedia.org/wiki/Xorshift#Initialization
 */
typedef struct PRNGSplitmix64 {
    u64 state;
} PRNGSplitmix64;

Result prng_splitmix64_seed(PRNGSplitmix64 *restrict prng, u64 seed);
Result prng_splitmix64_next(PRNGSplitmix64 *restrict prng, u64 *value);

/**
 * @brief Xorshiftr128+ pseudo random number generator.
 *
 * @note https://en.wikipedia.org/wiki/Xorshift#xorshift.2B
 */
typedef struct PRNGXorshift128p {
    u64 state[2];
} PRNGXorshiftr128p;

Result prng_xorshiftr128p_seed(PRNGXorshiftr128p *restrict prng, u64 seed);
Result prng_xorshiftr128p_next(PRNGXorshiftr128p *restrict prng, u64 *value);

#endif // !SUPPORT_ALGORITHM_RANDOM_H
