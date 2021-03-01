#include "../src/Object.hpp"

#include <gtest/gtest.h>

using namespace mdb;

TEST(ObjectTest, testEnumToString) {
    EXPECT_EQ("string", toString(ObjectType::kString));
    EXPECT_EQ("list", toString(ObjectType::kList));
    EXPECT_EQ("raw", toString(ObjectEncode::kRaw));
    EXPECT_EQ("hashtable", toString(ObjectEncode::kHashSet));
    EXPECT_EQ("hashtable", toString(ObjectEncode::kHashMap));
    EXPECT_EQ("rbtree", toString(ObjectEncode::kRBTree));

#ifndef NDEBUG
    EXPECT_DEATH(
        toString(static_cast<ObjectType>(42)),
        "unknow object type\nUnreachable executed at .*Object.cpp:20");
#else
    EXPECT_DEATH(static_cast<ObjectType>(42)), "");
#endif
}