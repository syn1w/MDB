#include "Util.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>

namespace mdb {

[[noreturn]] void mdb_unreachable_internal(const char* msg,
                                           const char* filename,
                                           std::uint32_t lineno) {
#ifndef NDEBUG
    if (msg) {
        std::cerr << msg << std::endl;
    }
    std::cerr << "Unreachable executed";
    if (filename) {
        std::cerr << " at " << filename << ":" << lineno;
    }
    std::cerr << "!\n";
#endif // !NDEBUG
    abort();
    MDB_BUILTIN_UNREACHABLE;
}

} // namespace mdb
