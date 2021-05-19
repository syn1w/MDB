#ifndef MDB_BASIC_SORTED_SET_HPP
#define MDB_BASIC_SORTED_SET_HPP

#include <set>

#include "String.hpp"

namespace mdb {

class TreeSet : public RefCountBase {
public:
    using Container = std::set<String, std::less<String>, Allocator<String>>;

    Container data;
};

} // namespace mdb

#endif // !MDB_BASIC_SORTED_SET_HPP