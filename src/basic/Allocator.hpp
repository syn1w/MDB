#ifndef MDB_BASIC_ALLOCATOR_HPP
#define MDB_BASIC_ALLOCATOR_HPP

#include <limits>
#include <new> // placement new

#include "ZMalloc.hpp"

namespace mdb {

template <typename T>
struct Allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;

    template <typename U>
    struct rebind {
        using other = Allocator<U>;
    };

    Allocator() noexcept {
    }
    Allocator(const Allocator<T>&) noexcept {
    }

    template <typename U>
    Allocator(const Allocator<U>&) noexcept {
    }

    template <typename U>
    Allocator& operator=(const Allocator<U>&) noexcept {
        return *this;
    }

    pointer allocate(size_type n) {
        return static_cast<pointer>(zmalloc(n * sizeof(T)));
    }

    void deallocate(pointer ptr, size_t /*n*/) {
        zfree(ptr);
    }

    pointer address(reference x) const noexcept {
        return std::addressof(x);
    }

    const_pointer address(const_reference x) const noexcept {
        return static_cast<const_pointer>(const_cast<reference>(x));
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    template <typename Obj, typename... Args>
    void construct(Obj* ptr, Args&&... args) {
        ::new (static_cast<void*>(ptr)) Obj(std::forward<Args>(args)...);
    }

    template <typename Obj>
    void destroy(Obj* ptr) {
        ptr->~T();
    }
};

} // namespace mdb

#endif // !MDB_BASIC_ALLOCATOR_HPP