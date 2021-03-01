#include "Object.hpp"

#include "Util.hpp"

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
    case ObjectType::kDict:
        return "dict";
    default:
        MDB_UNREACHABLE("unknow object type");
    }
}

const char* toString(ObjectEncode encode) {
    switch (encode) {
    case ObjectEncode::kRaw:
        return "raw";
    case ObjectEncode::kInteger:
        return "integer";
    case ObjectEncode::kEmbStr:
        return "embstr";
    case ObjectEncode::kHashSet:
        MDB_FALLTHROUGH;
    case ObjectEncode::kHashMap:
        return "hashtable";
    case ObjectEncode::kLinkedList:
        return "linkedlist";
    case ObjectEncode::kZipList:
        return "ziplist";
    case ObjectEncode::kIntSet:
        return "intset";
    case ObjectEncode::kRBTree:
        return "rbtree";
    default:
        MDB_UNREACHABLE("unknow object encode");
    }
}

} // namespace mdb