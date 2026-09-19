# Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)

add_library(kon-qi INTERFACE)

target_include_directories(kon-qi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_definitions(kon-qi
  INTERFACE
    $<IF:$<BOOL:${KON_QI_ENABLE_INLINE_ADDON}>,KON_QI_ENABLE_INLINE_ADDON,>
)

add_library(kon::qi ALIAS kon-qi)