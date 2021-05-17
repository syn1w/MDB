#include "../src/basic/String.hpp"

#include <cassert>
#include <cctype>
#include <climits>
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

    String str2{42L};
    EXPECT_EQ(str2.size(), 2);
    EXPECT_EQ(str2[0], '4');
    EXPECT_EQ(str2[1], '2');

    String str3{-2147483648L};
    EXPECT_EQ(str3.size(), 11);
    EXPECT_EQ(str3, String{"-2147483648"});

    String str4{2147483647L};
    EXPECT_EQ(str4.size(), 10);
    EXPECT_EQ(str4, String{"2147483647"});

    String str5{3.0};
    EXPECT_EQ(str5.size(), 1);
    EXPECT_EQ(str5, String{"3"});

    String str6{1.5};
    EXPECT_EQ(str6.size(), 3);
    EXPECT_EQ(str6, String{"1.5"});
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

TEST(StringTest, test6) {
    String str1 = "abc";
    str1.appendArgs(42, "def", 3.14);
    EXPECT_EQ(str1.size(), 12);
    str1.appendArgs();
    EXPECT_EQ(str1.size(), 12);
    EXPECT_EQ(str1[3], '4');
    EXPECT_EQ(str1[8], '3');
    EXPECT_EQ(str1[9], '.');
    EXPECT_EQ(str1[10], '1');
    EXPECT_EQ(str1[11], '4');
}

TEST(StringTest, test7) {
    String str1 = "123";
    str1.appendFmtStr("%d\t%s,%g", 42, "def", 3.14);
    EXPECT_EQ(str1.size(), 14);
    EXPECT_EQ(str1[3], '4');
    EXPECT_EQ(str1[10], '3');
    EXPECT_EQ(str1[11], '.');
    EXPECT_EQ(str1[12], '1');
    EXPECT_EQ(str1[13], '4');

    String str2;
    str2.appendFmtStr(
        "11111111111111111111111111111111111111111111111111111111"
        "1111111111111111111111111111111111111111111111111111111111111111111111"
        "11%d",
        42);
    EXPECT_EQ(str2.size(), 130);
}

TEST(StringTest, test8) {
    String str1 = "abcd1234";
    String str2 = str1.substr(4, 3);
    EXPECT_EQ(str2.size(), 3);
    EXPECT_EQ(str2[0], '1');
    EXPECT_EQ(str2[2], '3');

    String str3 = str1.substr(4);
    EXPECT_EQ(str3.size(), 4);
    EXPECT_EQ(str3[0], '1');
    EXPECT_EQ(str3[3], '4');
}

TEST(StringTest, test9) {
    String str1 = "abCD1234";
    str1.toLower();
    EXPECT_EQ(str1[0], 'a');
    EXPECT_EQ(str1[2], 'c');
    EXPECT_EQ(str1[3], 'd');
    EXPECT_EQ(str1[4], '1');
    str1.toUpper();
    EXPECT_EQ(str1[0], 'A');
    EXPECT_EQ(str1[1], 'B');
    EXPECT_EQ(str1[2], 'C');
    for (auto& ch : str1) {
        ch = std::tolower(ch);
    }
    EXPECT_EQ(str1[0], 'a');
    EXPECT_EQ(str1[2], 'c');
    EXPECT_EQ(str1[3], 'd');
    EXPECT_EQ(str1[4], '1');
}

TEST(StringTest, test10) {
    auto str1 = String("abcd\0efg");
    auto str2 = String("abcd\0efg");
    EXPECT_TRUE(str1 == str2);
    str2[3] = 'z';
    EXPECT_TRUE(str1 < str2);
}