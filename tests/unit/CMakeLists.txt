# Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(kon_qi_tests
    qi/enum.cpp
    qi/member.cpp
    qi/struct.cpp
    qi/addon_enum.cpp
    qi/addon_struct.cpp
)

target_link_libraries(kon_qi_tests PRIVATE
    Catch2::Catch2WithMain
    kon::qi
)