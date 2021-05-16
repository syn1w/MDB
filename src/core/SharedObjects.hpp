#ifndef MDB_CORE_SHARED_OBJECT_HPP
#define MDB_CORE_SHARED_OBJECT_HPP

#include <array>

#include "Object.hpp"

namespace mdb {

class SharedObjects {
public:
    static constexpr std::size_t kNumberSharedIntegers = 1024;

    static const SharedObjects& get() {
        static SharedObjects instance;
        return instance;
    }

    static const Object& getInteger(std::size_t idx);

private:
    std::array<Object, kNumberSharedIntegers> integers;

    SharedObjects();
};
} // namespace mdb

#endif // !MDB_CORE_SHARED_OBJECT_HPP