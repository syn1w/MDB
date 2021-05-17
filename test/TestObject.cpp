#include <cassert>
#include <gtest/gtest.h>

#include "../src/core/Object.hpp"
#include "../src/core/SharedObjects.hpp"

using namespace mdb;

TEST(ObjectTest, testToString) {
    EXPECT_EQ(std::string{"string"}, toString(ObjectType::kString));
    EXPECT_EQ(std::string{"list"}, toString(ObjectType::kList));
    EXPECT_EQ(std::string{"raw"}, toString(ObjectEncode::kRaw));
    EXPECT_EQ(std::string{"hash"}, toString(ObjectType::kHash));
    EXPECT_EQ(std::string{"hashtable"}, toString(ObjectEncode::kHT));
    EXPECT_EQ(std::string{"rbtree"}, toString(ObjectEncode::kRBTree));

#ifndef NDEBUG
    EXPECT_DEATH(toString(static_cast<ObjectType>(42)),
                 "unknow object type\nUnreachable executed at .*Object.cpp:.*");
#else
    EXPECT_DEATH(static_cast<ObjectType>(42)), "");
#endif
}

TEST(ObjectTest, testStringObject) {
    Object obj0;
    EXPECT_FALSE(obj0.hasValue());

    Object strObj1{42L};
    EXPECT_EQ(ObjectType::kString, strObj1.getType());
    EXPECT_EQ(ObjectEncode::kInt, strObj1.getEncode());
    EXPECT_EQ(42, strObj1.castToInt());

    Object strObj2 = Object::createString(42L);
    EXPECT_EQ(ObjectType::kString, strObj2.getType());
    EXPECT_EQ(ObjectEncode::kInt, strObj2.getEncode());
    EXPECT_EQ(42, strObj2.castToInt());

    Object strObj3 = Object::createString(20000L);
    EXPECT_EQ(ObjectType::kString, strObj3.getType());
    EXPECT_EQ(ObjectEncode::kInt, strObj3.getEncode());
    EXPECT_EQ(20000, strObj3.castToInt());

    Object strObj4{"test string", 11};
    EXPECT_EQ(ObjectType::kString, strObj4.getType());
    EXPECT_EQ(ObjectEncode::kRaw, strObj4.getEncode());
    EXPECT_EQ(String{"test string"}, *strObj4.castToString());

    Object strObj5 = strObj4;
    EXPECT_EQ(ObjectType::kString, strObj5.getType());
    EXPECT_EQ(ObjectEncode::kRaw, strObj5.getEncode());
    EXPECT_EQ(String{"test string"}, *strObj5.castToString());

    Object strObj6 = std::move(strObj4);
    EXPECT_TRUE(strObj6.hasValue());
    EXPECT_FALSE(strObj4.hasValue());
    EXPECT_TRUE(strObj5.hasValue());
    EXPECT_EQ(ObjectType::kString, strObj5.getType());
    EXPECT_EQ(ObjectEncode::kRaw, strObj5.getEncode());
    EXPECT_EQ(String{"test string"}, *strObj5.castToString());

    Object strObj7 = SharedObjects::getInteger(42);
    EXPECT_EQ(ObjectType::kString, strObj7.getType());
    EXPECT_EQ(ObjectEncode::kInt, strObj7.getEncode());
    EXPECT_EQ(42, strObj7.castToInt());
}