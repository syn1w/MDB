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

Object::Object(String&& str)
    : mType(ObjectType::kString), mEncode(ObjectEncode::kRaw), mLRU(0),
      mRefCount(1) {

    mValue = newValue<String>(std::move(str));
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
        mValue = newValue<String>(value);
    };
#else
#error "sizeof(void*) must be 8 or 4"
#endif
}

Object::Object(double value) : Object(String{value}) {
}

Object::Object(const char* ptr, std::size_t len) : Object(String{ptr, len}) {
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

Object Object::createString(double value) {
    return Object(value);
}

#define INIT_CONTAINER_VALUE(TYPE) Allocator<TYPE> alloc;

Object Object::createList() {
    // TODO: Support ZipList
    auto* value = newValue<LinkedList>();
    return Object{ObjectType::kList, ObjectEncode::kLinkedList, value};
}

Object Object::createHash() {
    // TODO: Support ZipList
    auto* value = newValue<HashMap>();
    return Object{ObjectType::kHash, ObjectEncode::kHT, value};
}

Object Object::createSet() {
    // TODO: Support IntSet
    auto* value = newValue<HashSet>();
    return Object{ObjectType::kSet, ObjectEncode::kHT, value};
}

Object Object::createZSet() {
    // TODO: Support ZipList
    auto* value = newValue<TreeSet>();
    return Object{ObjectType::kZSet, ObjectEncode::kRBTree, value};
}

Object::~Object() {
    if (--mRefCount > 0 || mValue == nullptr) {
        return;
    }

    // release
    switch (mType) {
    case ObjectType::kString:
        if (mEncode == ObjectEncode::kRaw) {
            deleteValue<String>();
        }
        break;
    case ObjectType::kList:
        if (mEncode == ObjectEncode::kLinkedList) {
            deleteValue<LinkedList>();
        }
        break;
    case ObjectType::kHash:
        if (mEncode == ObjectEncode::kHT) {
            deleteValue<HashMap>();
        }
        break;
    case ObjectType::kSet:
        if (mEncode == ObjectEncode::kHT) {
            deleteValue<HashSet>();
        }
        break;
    case ObjectType::kZSet:
        if (mEncode == ObjectEncode::kRBTree) {
            deleteValue<TreeSet>();
        }
        break;
    default:
        break;
    }

    mValue = nullptr;
}

} // namespace mdb