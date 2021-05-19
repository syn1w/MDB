add_library(MDBCore STATIC
    # Headers
    Object.hpp
    SharedObjects.hpp

    # Sources
    Object.cpp
    SharedObjects.cpp
)

target_link_libraries(MDBCore MDBBasic)