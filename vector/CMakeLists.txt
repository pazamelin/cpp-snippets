cmake_minimum_required(VERSION 3.1...3.19)

project(
        vector
        VERSION 1.0
        LANGUAGES CXX)

# Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the main library
SET(INCLUDE vector.hpp)
SET(SRC)
add_library(vector INTERFACE)

# Build options
SET(CMAKE_BUILD_TYPE Debug)
option(BUILD_TESTS "build tests executables" ON)

# Options' status
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")

## [testing]
enable_testing()
find_package(Catch2 REQUIRED)

macro(register_test TEST_NAME)
    if(BUILD_TESTS)
        # Tests need to be added as executables first
        add_executable(${TEST_NAME} ${TEST_NAME}.cpp)

        # Should be linked to the main library, as well as the Catch2 testing library
        target_link_libraries(${TEST_NAME} vector Catch2::Catch2WithMain)

        # If you register a test, then ctest and make test will run it.
        # You can also run examples and check the output, as well.
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME}) # Command can be a target
    endif()
endmacro(register_test)

register_test(unit_tests)