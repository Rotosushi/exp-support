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
 * @file support/types/scalar.h
 * @brief explicitly sized Scalar types.
 * plus some common functions not in the standard library.
 */

#ifndef SUPPORT_TYPES_SCALAR_H
#define SUPPORT_TYPES_SCALAR_H

#include "support/system/host.h"

#ifndef SUPPORT_SYSTEM_HOST_PROCESSOR_X86_64
#error "We currently only support x86_64 architectures."
#endif

#if defined(SUPPORT_SYSTEM_HOST_OS_LINUX)
/*
 * @[https://en.cppreference.com/w/c/language/arithmetic_types]
 *
 * x86_64 Linux uses the LP64 data model
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;

typedef signed char  i8;
typedef signed short i16;
typedef signed int   i32;
typedef signed long  i64;

#elif defined(SUPPORT_SYSTEM_HOST_OS_WINDOWS)
/*
 * @[https://en.cppreference.com/w/c/language/arithmetic_types]
 *
 * x86_64 Windows uses the LLP64 data model
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;

#else
#error "Unsupported platform: " SUPPORT_SYSTEM_HOST_OS_NAME
#endif

/*
 * @[https://en.cppreference.com/w/c/language/arithmetic_types]
 *
 * The C standard defines float as conforming to the IEEE 754-2008 binary32
 * format and double as conforming to the IEEE 754-2008 binary64 format.
 */
typedef float  f32;
typedef double f64;

/*
 * @[https://en.cppreference.com/w/c/language/arithmetic_types]
 *
 * The range of the unsigned integer types is from 0 to 2^n - 1, where n is the
 * number of bits in the type. The range of the signed integer types is from
 * -2^(n-1) to 2^(n-1) - 1, where n is the number of bits in the type.
 */
#define u8_MAX  0xFF
#define u16_MAX 0xFFFF
#define u32_MAX 0xFFFFFFFF
#define u64_MAX 0xFFFFFFFFFFFFFFFFull

#define i8_MAX  0x7F
#define i16_MAX 0x7FFF
#define i32_MAX 0x7FFFFFFF
#define i64_MAX 0x7FFFFFFFFFFFFFFFll

#define i8_MIN  0x80
#define i16_MIN 0x8000
#define i32_MIN 0x80000000
#define i64_MIN (i64)(0x8000000000000000ll)

#endif // !SUPPORT_TYPES_SCALAR_H
