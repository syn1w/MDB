add_library(MDBBasic STATIC
    # Headers
    Allocator.hpp
    HashMap.hpp
    HashSet.hpp
    LinkedList.hpp
    RefCountBase.hpp
    String.hpp
    TreeSet.hpp
    Util.hpp
    ZMalloc.hpp

    # Sources
    String.cpp
    Util.cpp
    ZMalloc.cpp
)