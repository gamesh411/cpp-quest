# Session 8: Shapeshifting

# Executable for combat demo
add_executable(combat_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session08
        tests/test_session08.cpp
    )
    target_link_libraries(test_session08 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session08_Tests COMMAND test_session08)
else()
    message(STATUS "Catch2 not found - tests for Session 8 will be skipped")
endif()
