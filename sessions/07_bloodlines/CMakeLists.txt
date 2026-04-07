# Session 7: Bloodlines

# Executable for entity demo
add_executable(entity_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session07
        tests/test_session07.cpp
    )
    target_link_libraries(test_session07 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session07_Tests COMMAND test_session07)
else()
    message(STATUS "Catch2 not found - tests for Session 7 will be skipped")
endif()
