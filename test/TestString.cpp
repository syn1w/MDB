#include "../src/String.hpp"
#include <gtest/gtest.h>

using namespace mdb;

TEST(StringTest, test1) {
    String str1;
    EXPECT_EQ(str1.size(), 0);
}

TEST(StringTest, test2) {
    String str2 = "I am a string";
    EXPECT_EQ(str2.size(), 13);
}