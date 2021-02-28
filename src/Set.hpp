#ifndef MDB_SET_HPP
#define MDB_SET_HPP

#include <unordered_set>

#include "Allocator.hpp"

namespace mdb {

template <typename T>
using Set = std::unordered_set<T, std::hash<T>, std::equal_to<T>, Allocator<T>>;

} // namespace mdb

#endif // !MDB_SET_HPP