#ifndef MDB_BASIC_SORTED_SET_HPP
#define MDB_BASIC_SORTED_SET_HPP

#include <set>

#include "Allocator.hpp"

namespace mdb {

template <typename T>
using SortedSet = std::set<T, std::less<T>, Allocator<T>>;

} // namespace mdb

#endif // !MDB_BASIC_SORTED_SET_HPP