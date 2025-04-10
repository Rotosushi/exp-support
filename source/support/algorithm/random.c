/**
 * Copyright (C) 2025 cade-weinberg
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

/**
 * @file support/algorithm/random.c
 * @brief pseudo random number generation functions.
 */

#include "support/algorithm/random.h"
#include "support/utility/null.h"

Result prng_splitmix64_seed(PRNGSplitmix64 *restrict prng, u64 seed) {
    if (prng == NULL) { return RESULT_NULL_TARGET; }
    prng->state = seed;
    return RESULT_SUCCESS;
}

Result prng_splitmix64_next(PRNGSplitmix64 *restrict prng, u64 *value) {
    if (prng == NULL) { return RESULT_NULL_SOURCE; }
    if (value == NULL) { return RESULT_NULL_TARGET; }

    u64 z  = (prng->state += 0x9E3779B97F4A7C15);
    z      = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
    z      = (z ^ (z >> 27)) * 0x94D049BB133111EB;
    *value = z ^ (z >> 31);
    return RESULT_SUCCESS;
}

Result prng_xorshiftr128p_seed(PRNGXorshiftr128p *restrict prng, u64 seed) {
    if (prng == NULL) { return RESULT_NULL_TARGET; }

    PRNGSplitmix64 splitmix;
    Result         result = prng_splitmix64_seed(&splitmix, seed);
    if (result != RESULT_SUCCESS) { return result; }

    result = prng_splitmix64_next(&splitmix, &prng->state[0]);
    if (result != RESULT_SUCCESS) { return result; }
    result = prng_splitmix64_next(&splitmix, &prng->state[1]);
    if (result != RESULT_SUCCESS) { return result; }
    return RESULT_SUCCESS;
}

Result prng_xorshiftr128p_next(PRNGXorshiftr128p *restrict prng, u64 *value) {
    if (prng == NULL) { return RESULT_NULL_SOURCE; }
    if (value == NULL) { return RESULT_NULL_TARGET; }

    u64       x    = prng->state[0];
    u64 const y    = prng->state[1];
    prng->state[0] = y;
    x ^= (x << 23);
    x ^= (x >> 17);
    x ^= y;
    prng->state[1] = x + y;

    *value = x;
    return RESULT_SUCCESS;
}
