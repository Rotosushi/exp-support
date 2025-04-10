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

configure_file(
    ${SUPPORT_INCLUDE_DIR}/support/system/host.h.in
    ${SUPPORT_INCLUDE_DIR}/support/system/host.h
)

set(SUPPORT_SOURCES
    ${SUPPORT_SOURCE_DIR}/support/algorithm/conversion.c
    ${SUPPORT_SOURCE_DIR}/support/algorithm/cstring.c
    ${SUPPORT_SOURCE_DIR}/support/algorithm/hash.c
    ${SUPPORT_SOURCE_DIR}/support/algorithm/memory.c
    ${SUPPORT_SOURCE_DIR}/support/algorithm/random.c

    ${SUPPORT_SOURCE_DIR}/support/types/result.c
    ${SUPPORT_SOURCE_DIR}/support/types/stream.c
    ${SUPPORT_SOURCE_DIR}/support/types/string_view.c

    ${SUPPORT_SOURCE_DIR}/support/utility/message.c
    ${SUPPORT_SOURCE_DIR}/support/utility/panic.c
)

add_library(support STATIC 
    ${SUPPORT_SOURCES}
)
target_include_directories(support PUBLIC ${SUPPORT_INCLUDE_DIR})
target_compile_options(support PUBLIC ${SUPPORT_C_FLAGS})
target_link_options(support PUBLIC ${SUPPORT_LD_FLAGS})
