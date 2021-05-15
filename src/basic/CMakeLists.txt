add_library(MDBBasic STATIC
    # Headers
    Allocator.hpp
    HashTable.hpp
    LinkedList.hpp
    Set.hpp
    SortedSet.hpp
    String.hpp
    Util.hpp
    ZMalloc.hpp

    # Sources
    Util.cpp
    ZMalloc.cpp
)