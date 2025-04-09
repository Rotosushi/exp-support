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
 * @file support/algorithm/cstring.h
 * @brief C-string utility functions.
 */

#ifndef SUPPORT_ALGORITHM_CSTRING_H
#define SUPPORT_ALGORITHM_CSTRING_H

#include "support/types/result.h"
#include "support/types/scalar.h"

Result cstring_length(char const *restrict cstring, u64 *length);

#endif // !SUPPORT_ALGORITHM_CSTRING_H
