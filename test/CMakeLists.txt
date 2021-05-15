add_executable(Tests
    TestMain.cpp
    TestString.cpp
    TestUtil.cpp
    TestZMalloc.cpp
    TestObject.cpp
)

target_include_directories(Tests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(Tests PRIVATE
    gtest
    pthread
    MDBBasic
    MDBCore
)

add_custom_target(UnitTests
    COMMAND ${PROJECT_BINARY_DIR}/test/Tests

    DEPENDS Tests
    COMMENT "MDB unit testing..."
)
