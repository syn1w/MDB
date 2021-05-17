// Double linked list.

#ifndef MDB_BASIC_LINKED_LIST_HPP
#define MDB_BASIC_LINKED_LIST_HPP

#include <list>

#include "String.hpp"

namespace mdb {

using LinkedList = std::list<String, Allocator<String>>;

} // namespace mdb

#endif // !MDB_BASIC_LINKED_LIST_HPP