#undef USE_TCMALLOC
#undef USE_JEMALLOC
#undef __APPLE__
#include "../src/ZMalloc.hpp"

#include <gtest/gtest.h>

using namespace mdb;

TEST(MallocTest, usedMemory) {
    int* iptr1 = static_cast<int*>(zmalloc(sizeof(int)));
    std::size_t usedMemory = sizeof(int) + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());
    double* dptr1 = static_cast<double*>(zmalloc(sizeof(double)));
    usedMemory += sizeof(double) + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    void* ptr1 = zmalloc(42);
    usedMemory += 42 + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    void* ptr2 = zmalloc(1000000);
    usedMemory += 1000000 + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    void* ptr3 = zmalloc(1024 * 1024 * 1024); // 1GiB
    usedMemory += 1024 * 1024 * 1024 + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    zfree(iptr1);
    usedMemory -= sizeof(int) + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    zfree(dptr1);
    usedMemory -= sizeof(double) + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    zfree(ptr1);
    usedMemory -= 42 + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    zfree(ptr2);
    usedMemory -= 1000000 + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());

    zfree(ptr3);
    usedMemory -= 1024 * 1024 * 1024 + sizeof(std::size_t);
    EXPECT_EQ(usedMemory, zmallocUsedMemory());
}