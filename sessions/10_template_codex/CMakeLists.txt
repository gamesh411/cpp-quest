# Session 10: Template Codex

# Executable for template demo
add_executable(template_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session10
        tests/test_session10.cpp
    )
    target_link_libraries(test_session10 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session10_Tests COMMAND test_session10)
else()
    message(STATUS "Catch2 not found - tests for Session 10 will be skipped")
endif()
