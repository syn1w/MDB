#ifndef MDB_CORE_OBJECT_HPP
#define MDB_CORE_OBJECT_HPP

#include "../basic/String.hpp"
#include <cstdint>

namespace mdb {

enum class ObjectType : std::uint32_t {
    kUnknown,
    kString,
    kList,
    kHash,
    kSet,
    kZSet,
};

enum class ObjectEncode : std::uint32_t {
    kUnknown,
    kInt,
    kEmbStr, // TODO: Support it
    kRaw,
    kHT,
    kLinkedList,
    KIntSet,  // TODO: Support it
    kZipList, // TODO: Support it
    kRBTree,  // Use rbtree instead of skiplist
};

class Object {
public:
    static const std::size_t kTypeBits = 4;
    static const std::size_t kEncodeBits = 4;
    static const std::size_t kLRUBits = 24;

public:
    Object()
        : mType(ObjectType::kUnknown), mEncode(ObjectEncode::kUnknown), mLRU(0),
          mRefCount(0), mValue(nullptr) {
    }

    Object(Object& rhs)
        : mType(rhs.mType), mEncode(rhs.mEncode), mLRU(rhs.mLRU),
          mRefCount(++rhs.mRefCount), mValue(rhs.mValue) {
    }

    Object(const Object& rhs)
        : mType(rhs.mType), mEncode(rhs.mEncode), mLRU(rhs.mLRU),
          mRefCount(++rhs.mRefCount), mValue(rhs.mValue) {
    }

    Object(Object&& rhs) noexcept
        : mType(rhs.mType), mEncode(rhs.mEncode), mLRU(rhs.mLRU),
          mRefCount(rhs.mRefCount), mValue(rhs.mValue) {
        rhs.mRefCount = 0;
        rhs.mValue = nullptr;
    }

    Object& operator=(Object& rhs) {
        mType = rhs.mType;
        mEncode = rhs.mEncode;
        mLRU = rhs.mLRU;
        mRefCount = ++rhs.mRefCount;
        mValue = rhs.mValue;

        return *this;
    }

    Object& operator=(const Object& rhs) {
        mType = rhs.mType;
        mEncode = rhs.mEncode;
        mLRU = rhs.mLRU;
        mRefCount = ++rhs.mRefCount;
        mValue = rhs.mValue;

        return *this;
    }

    Object& operator=(Object&& rhs) noexcept {
        mType = rhs.mType;
        mEncode = rhs.mEncode;
        mLRU = rhs.mLRU;
        mRefCount = rhs.mRefCount;
        mValue = rhs.mValue;

        rhs.mRefCount = 0;
        rhs.mValue = nullptr;

        return *this;
    }

    ~Object();

    Object(ObjectType type, ObjectEncode encode, void* ptr)
        : mType(type), mEncode(encode), mLRU(0), mRefCount(1), mValue(ptr) {
    }

    Object(std::int64_t value);
    Object(double value);
    Object(const char* ptr, std::size_t len);

    /// createString is optimized because shared objects are used first
    static Object createString(std::int64_t value);
    static Object createString(const char* ptr, std::size_t len);
    static Object createString(double value);

public:
    const String* castToString() const {
        return reinterpret_cast<String*>(mValue);
    }

    std::int64_t castToInt() const {
        return static_cast<std::int64_t>(
            reinterpret_cast<std::intptr_t>(mValue));
    }

    ObjectType getType() const {
        return mType;
    }

    ObjectEncode getEncode() const {
        return mEncode;
    }

    bool hasValue() const {
        return mValue != nullptr;
    }

private:
    // details
    void freeString();

    static constexpr std::size_t kPointerSize = sizeof(void*);
    static constexpr std::size_t kInt64Size = sizeof(std::int64_t);
    static constexpr std::size_t kInt32Size = sizeof(std::int32_t);

private:
    ObjectType mType : kTypeBits;
    ObjectEncode mEncode : kEncodeBits;
    std::uint32_t mLRU : kLRUBits;
    mutable std::int32_t mRefCount; // single thread

    void* mValue;
};

const char* toString(ObjectType type);
const char* toString(ObjectEncode encode);

} // namespace mdb

#endif // !MDB_CORE_OBJECT_HPP
