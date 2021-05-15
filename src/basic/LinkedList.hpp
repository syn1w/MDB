// Double linked list.

#ifndef MDB_BASIC_LINKED_LIST_HPP
#define MDB_BASIC_LINKED_LIST_HPP

#include <list>

#include "Allocator.hpp"

namespace mdb {

template <typename T>
using LinkedList = std::list<T, Allocator<T>>;

} // namespace mdb

#endif // !MDB_BASIC_LINKED_LIST_HPP