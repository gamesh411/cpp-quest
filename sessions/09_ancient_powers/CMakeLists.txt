# Session 9: Ancient Powers

# Executable for NPC demo
add_executable(npc_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session09
        tests/test_session09.cpp
    )
    target_link_libraries(test_session09 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session09_Tests COMMAND test_session09)
else()
    message(STATUS "Catch2 not found - tests for Session 9 will be skipped")
endif()
