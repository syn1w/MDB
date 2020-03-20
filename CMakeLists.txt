cmake_minimum_required(VERSION 3.0)
project(MDB VERSION 1.0.0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(src)

# Testing
option(TESTING "enable testing" OFF)
if (TESTING)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE ON)
    add_subdirectory(test)
endif (TESTING)
