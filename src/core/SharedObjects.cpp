#include "SharedObjects.hpp"

namespace mdb {

SharedObjects::SharedObjects() : integers({}) {
    // [0, kNumberSharedIntegers]
    for (std::size_t i = 0; i < kNumberSharedIntegers; ++i) {
        integers[i] = Object{static_cast<std::int64_t>(i)};
    }
}

const Object& SharedObjects::getInteger(std::size_t idx) {
    return get().integers[idx];
}

} // namespace mdb