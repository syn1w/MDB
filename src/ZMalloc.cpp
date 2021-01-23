#include "ZMalloc.hpp"

#include <atomic>
#include <cstdlib>
#include <iostream>

#ifdef HAVE_MALLOC_SIZE
static const std::size_t kPerfixSize = 0;
#else
static const std::size_t kPerfixSize = (sizeof(std::size_t));
#endif

#if defined(USE_TCMALLOC)
#define malloc(size) tc_malloc(size)
#define calloc(count, size) tc_calloc(count, size)
#define free(ptr) tc_free(ptr)
#elif defined(USE_JEMALLOC)
#define malloc(size) je_malloc(size)
#define calloc(count, size) je_calloc(count, size)
#define free(ptr) je_free(ptr)
#endif

static std::atomic_size_t usedMemory{0};

static void addUsedMemory(std::size_t n) noexcept {
    usedMemory.fetch_add(n, std::memory_order_relaxed);
}

static void subUsedMemory(std::size_t n) noexcept {
    usedMemory.fetch_sub(n, std::memory_order_relaxed);
}

static void zmallocDefaultOOM(std::size_t size) {
    std::cerr << "zmalloc: Out of memory trying to allocate " << size
              << "bytes\n";
    abort();
}

static void (*zmallocOOMHandler)(std::size_t) = zmallocDefaultOOM;

namespace mdb {

void zmallocSetOOMHandler(void (*handler)(std::size_t)) {
    zmallocOOMHandler = handler;
}

std::size_t zmallocUsedMemory(void) {
    return usedMemory.load(std::memory_order_relaxed);
}

// if there is no HAVE_MALLOC_SIZE, use sizoef(std::size_t) to
// hold the space allocated by ptr
//    +---------------------+---------------------------------+
//    | sizeof(std::size_t) |           user data...          |
//    +---------------------+---------------------------------+
//    ^                     ^
//    |                     |
// realptr                 ptr
//

void* zmalloc(std::size_t size) {
    void* ptr = malloc(size + kPerfixSize);

    if (!ptr) {
        zmallocOOMHandler(size);
    }

#ifdef HAVE_MALLOC_SIZE
    addUsedMemory(zmallocSize(ptr));
    return ptr;
#else
    *static_cast<std::size_t*>(ptr) = size;
    addUsedMemory(size + kPerfixSize);
    return static_cast<std::int8_t*>(ptr) + kPerfixSize;
#endif
}

void* zcalloc(std::size_t count, std::size_t size) {
    void* ptr = calloc(count, size);

    if (!ptr) {
        zmallocOOMHandler(count * size);
    }

#ifdef HAVE_MALLOC_SIZE
    addUsedMemory(zmallocSize(ptr));
    return ptr;
#else
    *static_cast<std::size_t*>(ptr) = size;
    addUsedMemory(count * size + kPerfixSize);
    return static_cast<std::uint8_t*>(ptr) + kPerfixSize;
#endif
}

#ifndef HAVE_MALLOC_SIZE
std::size_t zmallocSize(void* ptr) {
    void* realptr = static_cast<std::int8_t*>(ptr) - kPerfixSize;
    std::size_t size = *static_cast<std::size_t*>(realptr);
    return size + kPerfixSize;
}
#endif

void zfree(void* ptr) {
    if (ptr == nullptr) {
        return;
    }

#ifdef HAVE_MALLOC_SIZE
    subUsedMemory(zmallocSize(ptr));
    free(ptr);
#else
    void* realptr = static_cast<std::int8_t*>(ptr) - kPerfixSize;
    std::size_t size = *static_cast<std::size_t*>(realptr);
    subUsedMemory(size + kPerfixSize);
    free(realptr);
#endif
}

} // namespace mdb