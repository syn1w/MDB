add_library(MDBBasic STATIC
    # Headers
    Allocator.hpp
    HashMap.hpp
    LinkedList.hpp
    HashSet.hpp
    SortedSet.hpp
    String.hpp
    Util.hpp
    ZMalloc.hpp

    # Sources
    String.cpp
    Util.cpp
    ZMalloc.cpp
)