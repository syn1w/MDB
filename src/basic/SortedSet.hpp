#ifndef MDB_BASIC_SORTED_SET_HPP
#define MDB_BASIC_SORTED_SET_HPP

#include <set>

#include "String.hpp"

namespace mdb {

using TreeSet = std::set<String, std::less<String>, Allocator<String>>;

} // namespace mdb

#endif // !MDB_BASIC_SORTED_SET_HPP