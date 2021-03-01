#ifndef MDB_UTIL_HPP
#define MDB_UTIL_HPP

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

#endif // !MDB_UTIL_HPP