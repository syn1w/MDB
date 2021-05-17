#ifndef MDB_BASIC_HASH_SET_HPP
#define MDB_BASIC_HASH_SET_HPP

#include <unordered_set>

#include "String.hpp"

namespace mdb {

using HashSet = std::unordered_set<String, HashString, std::equal_to<String>,
                                   Allocator<String>>;

} // namespace mdb

#endif // !MDB_BASIC_HASH_SET_HPP