// Just like zmalloc
#ifndef MDB_ZMALLOC_HPP
#define MDB_ZMALLOC_HPP

#include <cstdint>

#if defined(USE_TCMALLOC)
#define ZMALLOC_LIB ("tcmalloc-" #TC_VERSION_MAJOR "." #TC_VERSION_MINOR)
#include <google/tcmalloc.h>
#if (TC_VERSION_MAJOR == 1 && TC_VERSION_MINOR >= 6 || TC_VERSION > 1)
#define HAVE_MALLOC_SIZE 1
#define zmallocSize(p) tc_malloc_size(p)
#else
#error "Newer version of tcmalloc required"
#endif

#elif defined(USE_JEMALLOC)
#define ZMALLOC_LIB                                                            \
    ("jemalloc-" #JEMALLOC_VERSION_MAJOR "." #JEMALLOC_VERSION_MINOR           \
     "." #JEMALLOC_VERSION_BUGFIX)
#include <jemalloc/jemalloc.h>
#if (JEMALLOC_VERSION_MAJOR == 2 && JEMALLOC_VERSION_MINOR >= 1) ||            \
    (JEMALLOC_VERSION_MAJOR > 2)
#define HAVE_MALLOC_SIZE 1
#define zmallocSize(p) je_malloc_usable_size(p)
#else
#error "Newer version of jemalloc required"
#endif

#elif defined(__APPLE__)
#include <malloc/malloc.h>
#define HAVE_MALLOC_SIZE 1
#define zmallocSize(p) malloc_size(p)
#endif

#ifndef ZMALLOC_LIB
#define ZMALLOC_LIB "libc"
#endif

namespace mdb {

void* zmalloc(std::size_t size);
void* zcalloc(std::size_t count, std::size_t size);
// realloc is not implemented, unless it is used
void zfree(void* ptr);
void zmallocSetOOMHandler(void (*handler)(std::size_t));

std::size_t zmallocUsedMemory(void);

#ifndef HAVE_MALLOC_SIZE
std::size_t zmallocSize(void* ptr);
#endif // !HAVE_MALLOC_SIZE

} // namespace mdb

#endif // !MDB_ZMALLOC_HPP