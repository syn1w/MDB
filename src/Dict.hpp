#ifndef MDB_DICT_HPP
#define MDB_DICT_HPP

#include <unordered_map>

#include "Allocator.hpp"

namespace mdb {

template <typename K, typename V>
using Dict = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>,
                                Allocator<std::pair<const K, V>>>;

} // namespace mdb

#endif // !MDB_DICT_HPP
