#ifndef MDB_BASIC_HASH_SET_HPP
#define MDB_BASIC_HASH_SET_HPP

#include <unordered_set>

#include "RefCountBase.hpp"
#include "String.hpp"

namespace mdb {

class HashSet : public RefCountBase {
public:
    using Container =
        std::unordered_set<String, HashString, std::equal_to<String>,
                           Allocator<String>>;

    Container data;
};

} // namespace mdb

#endif // !MDB_BASIC_HASH_SET_HPP