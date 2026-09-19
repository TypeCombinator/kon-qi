# Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.20)

option(KON_QI_ENABLE_INLINE_ADDON "Enable inline addon (annotation)." OFF)
option(KON_QI_BUILD_TESTS "Build tests." OFF)
option(KON_QI_BUILD_EXAMPLES "Build examples." OFF)

project(project_kon_qi LANGUAGES C CXX)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(KON_QI_IS_TOP_LEVEL_PROJECT ON)
else()
    set(KON_QI_IS_TOP_LEVEL_PROJECT OFF)
endif()

if(KON_QI_IS_TOP_LEVEL_PROJECT)
    include(FetchContent)

    # Set C++ standard.
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Add extra c/c++ flags.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILER_FLAGS}")

    # include(cmake/module/fmt.cmake)
endif()

add_subdirectory(kon)

if(KON_QI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(KON_QI_BUILD_TESTING)
    include(cmake/module/Catch2.cmake)
    add_subdirectory(tests/unit)

    # include(cmake/module/GoogleBenchmark.cmake)
    # add_subdirectory(tests/bench)
endif()