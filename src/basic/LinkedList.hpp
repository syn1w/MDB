// Double linked list.

#ifndef MDB_BASIC_LINKED_LIST_HPP
#define MDB_BASIC_LINKED_LIST_HPP

#include <list>

#include "RefCountBase.hpp"
#include "String.hpp"

namespace mdb {

class LinkedList : public RefCountBase {
public:
    using Container = std::list<String, Allocator<String>>;

    Container data;
};

} // namespace mdb

#endif // !MDB_BASIC_LINKED_LIST_HPP