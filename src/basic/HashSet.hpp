#ifndef MDB_BASIC_HASH_SET_HPP
#define MDB_BASIC_HASH_SET_HPP

#include <unordered_set>

#include "Allocator.hpp"

namespace mdb {

template <typename T>
using Set = std::unordered_set<T, std::hash<T>, std::equal_to<T>, Allocator<T>>;

} // namespace mdb

#endif // !MDB_BASIC_HASH_SET_HPP