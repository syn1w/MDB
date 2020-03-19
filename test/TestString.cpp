#include "../src/String.hpp"
#include <gtest/gtest.h>

using namespace mdb;

// Function test
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
    EXPECT_EQ(*str.begin(), 'I');
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

TEST(StringTest, test3) {
    String str1 = "............";
    EXPECT_EQ(str1.length(), 12);
    for (char ch : str1) {
        EXPECT_EQ(ch, '.');
    }
}

TEST(StringTest, test4) {
    String str1;
    str1 += "abcd";
    EXPECT_EQ(str1.size(), 4);
    EXPECT_EQ(str1[0], 'a');
    EXPECT_EQ(str1[3], 'd');
    EXPECT_EQ(str1[2], 'c');
    str1 += "dcba";
    EXPECT_EQ(str1.size(), 8);
    EXPECT_EQ(str1[7], 'a');

    str1.append("1234\0hijk", 9);
    EXPECT_EQ(str1.size(), 17);
    EXPECT_EQ(str1[8], '1');
    EXPECT_EQ(str1[12], '\0');
    EXPECT_EQ(str1[13], 'h');
}

TEST(StringTest, test5) {
    String str1 = "abc";
    str1 = "1234";
    EXPECT_EQ(str1.size(), 4);
    EXPECT_EQ(str1[0], '1');
    EXPECT_EQ(str1[4], '\0');

    str1.assign("abc\0def");
    EXPECT_EQ(str1.size(), 3);
    EXPECT_EQ(str1[0], 'a');
    EXPECT_EQ(str1[3], '\0');

    str1.assign("qwe\0rty", 7);
    EXPECT_EQ(str1.size(), 7);
    EXPECT_EQ(str1[0], 'q');
    EXPECT_EQ(str1[3], '\0');
    EXPECT_EQ(str1[4], 'r');
    EXPECT_EQ(str1[7], '\0');
}