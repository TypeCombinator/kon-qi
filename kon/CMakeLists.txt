# SPDX-FileCopyrightText: 2026 TypeCombinator <typecombinator@foxmail.com>
#
# SPDX-License-Identifier: BSD 3-Clause

add_library(kon-qi INTERFACE)

target_include_directories(kon-qi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(kon::qi ALIAS kon-qi)