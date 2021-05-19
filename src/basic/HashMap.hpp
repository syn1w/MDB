#ifndef MDB_BASIC_HASH_MAP_HPP
#define MDB_BASIC_HASH_MAP_HPP

#include <unordered_map>

#include "RefCountBase.hpp"
#include "String.hpp"

namespace mdb {

class HashMap : public RefCountBase {
public:
    using Container =
        std::unordered_map<String, String, HashString, std::equal_to<String>,
                           Allocator<std::pair<const String, String>>>;

    Container data;
};

} // namespace mdb

#endif // !MDB_BASIC_HASH_MAP_HPP
