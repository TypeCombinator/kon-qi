# AddressSanitizer options for the custom ASan build configuration.

if(MSVC) # For cl.exe or clang-cl.exe.
    # Reference: https://learn.microsoft.com/en-us/cpp/build/reference/oy-frame-pointer-omission?view=msvc-170
    set(KON_QI_SANITIZER_COMPILE_OPTIONS -fsanitize=address /Oy-)
    set(KON_QI_SANITIZER_LINK_OPTIONS /INCREMENTAL:NO)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        execute_process(
            COMMAND "${CMAKE_CXX_COMPILER}" /clang:-print-resource-dir
            OUTPUT_VARIABLE KON_QI_CLANG_CL_RESOURCE_DIR
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(KON_QI_CLANG_CL_RT_DIR "${KON_QI_CLANG_CL_RESOURCE_DIR}/lib/windows")
        list(APPEND KON_QI_SANITIZER_LINK_OPTIONS
            "/libpath:${KON_QI_CLANG_CL_RT_DIR}"
            "clang_rt.asan_dynamic-x86_64.lib"
            "/wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib"
        )
    endif()
elseif(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # For clang.exe.
    set(KON_QI_SANITIZER_COMPILE_OPTIONS -fsanitize=address -fno-omit-frame-pointer)
    set(KON_QI_SANITIZER_LINK_OPTIONS -fsanitize=address -static-libsan)
else() # For gcc or clang.
    set(KON_QI_SANITIZER_COMPILE_OPTIONS -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=all)
    set(KON_QI_SANITIZER_LINK_OPTIONS -fsanitize=address,undefined)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # GCC's -Wmaybe-uninitialized false-positives inside libstdc++ <regex>
        # once ASan instrumentation changes inlining decisions; google
        # benchmark builds with -Werror, so silence the bogus warning.
        list(APPEND KON_QI_SANITIZER_COMPILE_OPTIONS -Wno-maybe-uninitialized)
    endif()
endif()