#ifndef MDB_UTIL_HPP
#define MDB_UTIL_HPP

#include <cstdint>

namespace mdb {

[[noreturn]]
void mdb_unreachable_internal(const char* msg, const char* filename,
                              std::uint32_t lineno);

} // namespace mdb

#define MDB_UNREACHABLE(msg) \
    ::mdb::mdb_unreachable_internal(msg, __FILE__, __LINE__)

#if __has_builtin(__builtin_unreachable)
# define MDB_BUILTIN_UNREACHABLE __builtin_unreachable()
#elif defined(_MSC_VER)
#define MDB_BUILTIN_UNREACHABLE __assume(false)
#else
#define MDB_BUILTIN_UNREACHABLE
#endif 

#endif // !MDB_UTIL_HPP