#ifndef MDB_BASIC_REF_COUNT_BASE_HPP
#define MDB_BASIC_REF_COUNT_BASE_HPP

#include <cassert>
#include <cstdint>

#include "Allocator.hpp"

namespace mdb {

class RefCountBase {
protected:
    RefCountBase() : mRefCount(0) {
    }
    RefCountBase(const RefCountBase&) : mRefCount(0) {
    }

    void retain() const {
        ++mRefCount;
    }

    template <typename T>
    void release(T* ptr) const {
        assert(mRefCount > 0 && "Reference count must be greater than 0");
        if (--mRefCount == 0) {
            Allocator<T> alloc;
            alloc.destroy(ptr);
            alloc.deallocate(ptr, 0 /*unused*/);
        }
    }

    friend class Object;

protected:
    // single thread, so not thread safe
    mutable std::int32_t mRefCount;
};

} // namespace mdb

#endif // MDB_BASIC_REF_COUNT_BASE_HPP