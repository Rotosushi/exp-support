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
 * @file support/utility/ansi_color_codes.h
 * @brief ANSI color codes for terminal output.
 *
 * @warning The color codes may not work on all platforms.They are intended for
 * use with terminals that support ANSI escape codes.
 */

#ifndef SUPPORT_UTILITY_ANSI_COLOR_CODES_H
#define SUPPORT_UTILITY_ANSI_COLOR_CODES_H

#define ANSI_COLOR_RESET     "\033[0m"
#define ANSI_COLOR_BLACK     "\033[30m"
#define ANSI_COLOR_RED       "\033[31m"
#define ANSI_COLOR_GREEN     "\033[32m"
#define ANSI_COLOR_YELLOW    "\033[33m"
#define ANSI_COLOR_BLUE      "\033[34m"
#define ANSI_COLOR_MAGENTA   "\033[35m"
#define ANSI_COLOR_CYAN      "\033[36m"
#define ANSI_COLOR_WHITE     "\033[37m"
#define ANSI_COLOR_BOLD      "\033[1m"
#define ANSI_COLOR_UNDERLINE "\033[4m"

#endif // !SUPPORT_UTILITY_ANSI_COLOR_CODES_H
