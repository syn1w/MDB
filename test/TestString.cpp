#include "../src/String.hpp"
#include <gtest/gtest.h>

using namespace mdb;

TEST(StringTest, test0) {
    String str;
    EXPECT_EQ(str.size(), 0);
    EXPECT_TRUE(str.isEmpty());
}

TEST(StringTest, test1) {
    String str = "I am a string";
    EXPECT_EQ(str.size(), 13);
    str.append(3, '!');
    EXPECT_EQ(str.size(), 16);
    EXPECT_EQ(str[15], '!');
    EXPECT_EQ(str[16], '\0');
    EXPECT_FALSE(str.isEmpty());
    str.clear();
    EXPECT_TRUE(str.isEmpty());
    EXPECT_EQ(str.size(), 0);

    String str1 = "...";
    str.swap(str1);
    EXPECT_EQ(str1.size(), 0);
    EXPECT_EQ(str.size(), 3);
    EXPECT_EQ(str[0], '.');
}

TEST(StringTest, test2) {
    String str1 = String{"abcd\0dcba", 9};
    EXPECT_EQ(str1.size(), 9);
    auto str2 = str1;
    EXPECT_EQ(str1, str2);
    str2 += "!!!";
    EXPECT_EQ(str2.size(), 12);
}