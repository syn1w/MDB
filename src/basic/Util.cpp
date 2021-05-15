#include "Util.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>

#if defined __has_builtin
#if __has_builtin(__builtin_unreachable)
#define MDB_BUILTIN_UNREACHABLE __builtin_unreachable()
#endif // __has_builtin(__builtin_unreachable)
#elif defined(_MSC_VER)
#define MDB_BUILTIN_UNREACHABLE __assume(false)
#else
#define MDB_BUILTIN_UNREACHABLE
#endif // defined __has_builtin

[[noreturn]] void mdb::details::mdb_unreachable_internal(const char* msg,
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