# Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)

get_filename_component(CURRENT_TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${CURRENT_TARGET}
  main.cpp
)

target_link_libraries(${CURRENT_TARGET}
  PRIVATE
  kon::qi
)