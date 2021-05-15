#ifndef MDB_BASIC_UTIL_HPP
#define MDB_BASIC_UTIL_HPP

#include <cstdint>

namespace mdb {

namespace details {
[[noreturn]] void mdb_unreachable_internal(const char* msg,
                                           const char* filename,
                                           std::uint32_t lineno);
} // namespace details
} // namespace mdb

#define MDB_UNREACHABLE(msg)                                                   \
    ::mdb::details::mdb_unreachable_internal(msg, __FILE__, __LINE__)

#if __cplusplus >= 201703L
#define MDB_FALLTHROUGH [[fallthrough]]
#elif defined(__clang__) && defined(__has_cpp_attribute)
#if __has_cpp_attribute(clang::fallthrough)
#define MDB_FALLTHROUGH [[clang::fallthrough]]
#endif
#elif defined(__GNUC__) && __GNUC__ > 6
#define MDB_FALLTHROUGH [[gnu::fallthrough]]
#else
#define MDB_FALLTHROUGH
#endif

#endif // !MDB_BASIC_UTIL_HPP