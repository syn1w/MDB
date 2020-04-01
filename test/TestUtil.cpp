#include "../src/Util.hpp"

#include <gtest/gtest.h>

using namespace mdb;

TEST(UtilTest, test1) {
#ifndef NDEBUG
    EXPECT_DEATH(MDB_UNREACHABLE("test"), 
        "test\nUnreachable executed at .*TestUtil.cpp:8");
#else
    EXPECT_DEATH(MDB_UNREACHABLE("test"), "");
#endif
}