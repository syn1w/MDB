set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
    ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
)

add_subdirectory(basic)
add_subdirectory(core)
add_subdirectory(mdb)