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
 * @file support/algorithm/conversion.h
 * @brief conversion functions.
 */

#ifndef SUPPORT_ALGORITHM_CONVERSION_H
#define SUPPORT_ALGORITHM_CONVERSION_H

#include "support/types/result.h"
#include "support/types/scalar.h"

u64    convert_base_10_u64_buffer_length(u64 value);
Result convert_base_10_u64(u64 value, char *restrict buffer, u64 buffer_length);

u64    convert_base_10_i64_buffer_length(i64 value);
Result convert_base_10_i64(i64 value, char *restrict buffer, u64 buffer_length);

#endif // !SUPPORT_ALGORITHM_CONVERSION_H
