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

enable_testing()

# list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

catch_discover_tests(kon_qi_tests
  DL_PATHS
    # Set by cmake/module/asan.cmake， it's non-empty only when building
    # with clang-cl and using ASan.
    "${KON_QI_CLANG_CL_RT_DIR}"
)