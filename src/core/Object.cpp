#include "Object.hpp"

#include <limits>

#include "../basic/String.hpp"
#include "../basic/Util.hpp"
#include "SharedObjects.hpp"

namespace mdb {

const char* toString(ObjectType type) {
    switch (type) {
    case ObjectType::kString:
        return "string";
    case ObjectType::kList:
        return "list";
    case ObjectType::kSet:
        return "set";
    case ObjectType::kZSet:
        return "zset";
    case ObjectType::kHash:
        return "hash";
    default:
        MDB_UNREACHABLE("unknow object type");
    }
}

const char* toString(ObjectEncode encode) {
    switch (encode) {
    case ObjectEncode::kInt:
        return "int";
    case ObjectEncode::kEmbStr:
        return "embstr";
    case ObjectEncode::kRaw:
        return "raw";
    case ObjectEncode::kHT:
        return "hashtable";
    case ObjectEncode::kLinkedList:
        return "linkedlist";
    case ObjectEncode::kZipList:
        return "ziplist";
    case ObjectEncode::KIntSet:
        return "intset";
    case ObjectEncode::kRBTree:
        return "rbtree";
    default:
        MDB_UNREACHABLE("unknow object encode");
    }
}

Object::Object(std::int64_t value)
    : mType(ObjectType::kString), mEncode(ObjectEncode::kInt), mLRU(0),
      mRefCount(1) {

#if (kPointerSize == kInt64Size)
    mValue = reinterpret_cast<void*>(value);
#elif (kPointerSize == kInt32Size)
    if (value >= std::numeric_limits<std::int32_t>::min() &&
        value <= std::numeric_limits<std::int32_t>::max()) {
        mValue = reinterpret_cast<void*>(value);
    } else {
        mEncode = ObjectEncode::kRaw;
        mValue = new String{value};
    };
#else
#error "sizeof(void*) must be 8 or 4"
#endif
}

Object::Object(const char* ptr, std::size_t len)
    : mType(ObjectType::kString), mEncode(ObjectEncode::kRaw), mLRU(0),
      mRefCount(1), mValue(new String{ptr, len}) {
}

Object Object::createString(std::int64_t value) {
    constexpr std::int64_t kNumSharedIntegers =
        static_cast<std::int64_t>(SharedObjects::kNumberSharedIntegers);
    if (value >= 0 && value < kNumSharedIntegers) {
        return SharedObjects::getInteger(value);
    }

    return Object{value};
}

Object Object::createString(const char* ptr, std::size_t len) {
    // TODO: Support embstr
    return Object(ptr, len);
}

Object::~Object() {
    if (--mRefCount > 0) {
        return;
    }

    // release
    switch (mType) {
    case ObjectType::kString:
        freeString();
        break;

    default:
        break;
    }

    mValue = nullptr;
}

void Object::freeString() {
    if (mEncode == ObjectEncode::kRaw) {
        delete castToString();
    }
}

} // namespace mdb