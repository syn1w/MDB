#ifndef MDB_OBJECT_HPP
#define MDB_OBJECT_HPP

#include <cstdint>

namespace mdb {

enum class ObjectType : std::uint32_t {
    kString, // raw, integer, embstr?
    kList,   // linkedlist, ziplist?
    kSet,    // hashset, intset?
    kZSet,   // rbtree, ziplist?
    kDict,   // hashtable, ziplist?
};

enum class ObjectEncode : std::uint32_t {
    kRaw,
    kInteger,
    kEmbStr, // TODO: Support it
    kHashSet,
    kHashMap,
    kLinkedList,
    kZipList, // TODO: Support it
    kIntSet,  // TODO: Support it
    kRBTree,
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

#endif // !MDB_OBJECT_HPP
