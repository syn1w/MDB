cmake_minimum_required(VERSION 3.0)
project(MDB VERSION 1.0.0)

if (NOT UNIX)
    message(FATAL_ERROR "Required Unix operating system")
endif ()

set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to conform to")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")

add_compile_options(-Wall -Wextra)

add_subdirectory(src)

# Testing
option(TESTING "enable testing" ON)
if (TESTING)
    enable_testing()
    set(CTEST_OUTPUT_ON_FAILURE ON)
    add_subdirectory(test)
endif (TESTING)
