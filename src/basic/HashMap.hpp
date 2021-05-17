#ifndef MDB_BASIC_HASH_MAP_HPP
#define MDB_BASIC_HASH_MAP_HPP

#include <unordered_map>

#include "String.hpp"

namespace mdb {

using HashMap =
    std::unordered_map<String, String, HashString, std::equal_to<String>,
                       Allocator<std::pair<const String, String>>>;

} // namespace mdb

#endif // !MDB_BASIC_HASH_MAP_HPP
