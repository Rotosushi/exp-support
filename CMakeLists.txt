# Copyright (C) 2025 cade-weinberg
# 
# This file is part of exp-support.
# 
# exp-support is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# exp-support is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with exp-support.  If not, see <https://www.gnu.org/licenses/>.
cmake_minimum_required(VERSION 3.20)

message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "CMake generator: ${CMAKE_GENERATOR}")

project(exp-support 
    LANGUAGES C 
    VERSION 0.0.1
    DESCRIPTION "A library of C functions and types to support the exp compiler."
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

message(STATUS "Host System: ${CMAKE_HOST_SYSTEM_NAME}")

set(SUPPORT_SYSTEM_HOST_OS_NAME ${CMAKE_HOST_SYSTEM_NAME})

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(SUPPORT_SYSTEM_HOST_LINUX true)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(SUPPORT_SYSTEM_HOST_WINDOWS true)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_HOST_SYSTEM_NAME}")
endif()

message(STATUS "Host Processor: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

set(SUPPORT_SYSTEM_HOST_PROCESSOR_NAME ${CMAKE_HOST_SYSTEM_PROCESSOR})

if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64"
   OR CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(SUPPORT_SYSTEM_HOST_PROCESSOR_X86_64 true)
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
endif()

message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")

set(SUPPORT_SYSTEM_HOST_COMPILER_NAME ${CMAKE_C_COMPILER_ID})

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(SUPPORT_SYSTEM_HOST_COMPILER_GCC true)
    set(WARNINGS -Wall -Wextra -Wpedantic -Wconversion -Wdeprecated -Werror)
    set(SANITIZERS -fsanitize=address,undefined,leak)
    set(PROFILING -pg)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(SUPPORT_SYSTEM_HOST_COMPILER_CLANG true)
    set(WARNINGS -Wall -Wextra -Wpedantic -Wconversion -Wdeprecated -Werror)
    set(SANITIZERS -fsanitize=address,undefined,leak)
    set(PROFILING -pg)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(SUPPORT_SYSTEM_HOST_COMPILER_MSVC true)
    set(WARNINGS /W4 /WX)
    set(SANITIZERS /fsanitize=address)
    set(PROFILING)
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
endif()

set(SUPPORT_C_FLAGS ${WARNINGS})
set(SUPPORT_LD_FLAGS)

set(SUPPORT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SUPPORT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(SUPPORT_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE STREQUAL "Sanitize")
    message(STATUS "Building with sanitizers: ${SANITIZERS}")
    set(SUPPORT_C_FLAGS "${SUPPORT_C_FLAGS} ${SANITIZERS}")
    set(SUPPORT_LD_FLAGS "${SUPPORT_LD_FLAGS} ${SANITIZERS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Profile")
    message(STATUS "Building with profiling: ${PROFILING}")
    set(SUPPORT_C_FLAGS "${SUPPORT_C_FLAGS} ${PROFILING}")
    set(SUPPORT_LD_FLAGS "${SUPPORT_LD_FLAGS} ${PROFILING}")
endif()

message(STATUS "C Flags: ${SUPPORT_C_FLAGS}")
message(STATUS "LD Flags: ${SUPPORT_LD_FLAGS}")

add_subdirectory(${SUPPORT_SOURCE_DIR})

include(CTest)
add_subdirectory(${SUPPORT_TEST_DIR})

