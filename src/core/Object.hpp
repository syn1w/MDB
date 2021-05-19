#ifndef MDB_CORE_OBJECT_HPP
#define MDB_CORE_OBJECT_HPP

#include "../basic/HashMap.hpp"
#include "../basic/HashSet.hpp"
#include "../basic/LinkedList.hpp"
#include "../basic/String.hpp"
#include "../basic/TreeSet.hpp"
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
    kIntSet,  // TODO: Support it
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
          mValue(nullptr) {
    }

    Object(ObjectType type, ObjectEncode encode, RefCountBase* ptr)
        : mType(type), mEncode(encode), mLRU(0), mValue(ptr) {
        if (mValue && mEncode != ObjectEncode::kInt) {
            mValue->retain();
        }
    }

    Object(const Object& rhs)
        : mType(rhs.mType), mEncode(rhs.mEncode), mLRU(rhs.mLRU),
          mValue(rhs.mValue) {
        if (rhs.mValue && mEncode != ObjectEncode::kInt) {
            rhs.mValue->retain();
        }
    }

    Object(Object&& rhs) noexcept
        : mType(rhs.mType), mEncode(rhs.mEncode), mLRU(rhs.mLRU),
          mValue(rhs.mValue) {
        rhs.mValue = nullptr;
    }

    Object& operator=(const Object& rhs) {
        mType = rhs.mType;
        mEncode = rhs.mEncode;
        mLRU = rhs.mLRU;
        mValue = rhs.mValue;
        if (rhs.mValue && mEncode != ObjectEncode::kInt) {
            rhs.mValue->retain();
        }

        return *this;
    }

    Object& operator=(Object&& rhs) noexcept {
        mType = rhs.mType;
        mEncode = rhs.mEncode;
        mLRU = rhs.mLRU;
        mValue = rhs.mValue;
        rhs.mValue = nullptr;

        return *this;
    }

    ~Object();

    Object(std::int64_t value);
    Object(double value);
    Object(const char* ptr, std::size_t len);

    // createString is optimized because shared objects are used first
    static Object createString(std::int64_t value);
    static Object createString(double value);
    static Object createString(const char* ptr, std::size_t len);

    static Object createList();
    static Object createHash();
    static Object createSet();
    static Object createZSet();

public:
    template <typename R>
    R* castTo() const {
        return reinterpret_cast<R*>(mValue);
    }

    std::int64_t castToInt() const {
        assert(mType == ObjectType::kString && mEncode == ObjectEncode::kInt);
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
    // Constructing from String rvalue reference
    // Only as a delegate constructor and therefore set to private
    Object(String&& str);

private:
    // details
    template <typename T, typename... Args>
    static T* newValue(Args&&... args) {
        Allocator<T> alloc;
        T* value = alloc.allocate(sizeof(T));
        alloc.construct(value, std::forward<Args>(args)...);

        return value;
    }

    static constexpr std::size_t kPointerSize = sizeof(void*);
    static constexpr std::size_t kInt64Size = sizeof(std::int64_t);
    static constexpr std::size_t kInt32Size = sizeof(std::int32_t);

private:
    ObjectType mType : kTypeBits;
    ObjectEncode mEncode : kEncodeBits;
    std::uint32_t mLRU : kLRUBits;

    RefCountBase* mValue;
};

const char* toString(ObjectType type);
const char* toString(ObjectEncode encode);

} // namespace mdb

#endif // !MDB_CORE_OBJECT_HPP
