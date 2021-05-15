#include "Object.hpp"

#include "../basic/Util.hpp"

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

} // namespace mdb