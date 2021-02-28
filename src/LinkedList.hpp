// Double linked list.

#ifndef MDB_LINKED_LIST_HPP
#define MDB_LINKED_LIST_HPP

#include <list>

#include "Allocator.hpp"

namespace mdb {

template <typename T>
using LinkedList = std::list<T, Allocator<T>>;

} // namespace mdb

#endif // !MDB_LINKED_LIST_HPP