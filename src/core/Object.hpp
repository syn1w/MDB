#ifndef MDB_CORE_OBJECT_HPP
#define MDB_CORE_OBJECT_HPP

#include <cstdint>

namespace mdb {

enum class ObjectType : std::uint32_t {
    kString,
    kList,
    kHash,
    kSet,
    kZSet,
};

enum class ObjectEncode : std::uint32_t {
    kInt,
    kEmbStr, // TODO: Support it
    kRaw,
    kHT,
    kLinkedList,
    KIntSet,   // TODO: Support it
    kZipList,  // TODO: Support it
    kRBTree,   // Use rbtree instead of skiplist
};

class Object {
public:
    static const std::size_t kTypeBits = 4;
    static const std::size_t kEncodeBits = 4;
    static const std::size_t kLRUBits = 24;

public:
    Object(ObjectType type, ObjectEncode encode);

private:
    ObjectType mType : kTypeBits;
    ObjectEncode mEncode : kEncodeBits;
    std::uint32_t mLRU : kLRUBits;

    void* mValue;
};

const char* toString(ObjectType type);
const char* toString(ObjectEncode encode);

} // namespace mdb

#endif // !MDB_CORE_OBJECT_HPP
