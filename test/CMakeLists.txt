add_executable(Tests
    TestMain.cpp
    TestString.cpp
    TestUtil.cpp
    ${PROJECT_SOURCE_DIR}/src/Util.cpp
)

target_include_directories(Tests 
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

find_package(GTest CONFIG REQUIRED)

if(WIN32)
    target_link_libraries(Tests PRIVATE
        GTest::gtest
    )
elseif(UNIX)
    target_link_libraries(Tests PRIVATE
        gtest
        pthread
    )
endif (WIN32)

add_test(NAME AllTest
    COMMAND ./Tests
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
)