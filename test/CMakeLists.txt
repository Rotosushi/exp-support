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

set(TestSources 
    ${SUPPORT_TEST_DIR}/algorithm/conversion_tests.c
    ${SUPPORT_TEST_DIR}/algorithm/cstring_tests.c
    ${SUPPORT_TEST_DIR}/algorithm/memory_tests.c
)

function(create_test test_path)
    cmake_path(GET test_path STEM test_name)
    add_executable(${test_name} ${test_path})
    target_include_directories(${test_name} PRIVATE ${SUPPORT_INCLUDE_DIR})
    target_link_libraries(${test_name} PRIVATE support)
    target_compile_options(${test_name} PRIVATE ${SUPPORT_C_FLAGS})
    target_link_options(${test_name} PRIVATE ${SUPPORT_LD_FLAGS})
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

foreach(test ${TestSources})
    create_test(${test})
endforeach()