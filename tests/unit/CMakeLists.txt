add_executable(kon_qi_tests
    qi/addon.cpp
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