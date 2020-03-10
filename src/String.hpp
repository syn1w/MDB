// Simple dynamic string library.
// Using String instead of std::string for binary security.
#ifndef STRING_HPP
#define STRING_HPP

#include <cassert>
#include <cstring>
#include <vector>

namespace mdb {

class String {
public:
    using SizeType  = std::size_t;
    using ValueType = char;

public:
    String() : mBuffer() { }

    String(const void* data, SizeType len) 
        : mBuffer(static_cast<const ValueType*>(data),
                  static_cast<const ValueType*>(data) + len) {
    }

    String(const ValueType* str) : String(str, std::strlen(str)) { }

    String(const String&) = default;
    String(String&&) noexcept = default;

    String& operator=(const String&) = default;
    String& operator=(String&&) noexcept = default;

    ~String() noexcept = default;

    SizeType size() const {
        return mBuffer.size();
    }

    SizeType length() const {
        return mBuffer.size();
    }

    bool isEmpty() const {
        return mBuffer.size() == 0;
    }

    SizeType capacity() const {
        return mBuffer.capacity();
    }

    char& operator[](SizeType pos) {
        assert(pos <= size());
        return mBuffer[pos];
    }

    const char& operator[](SizeType pos) const {
        assert(pos <= size());
        return mBuffer[pos];
    }

    const ValueType* c_str() const {
        return mBuffer.data();
    }

    const void* data() const {
        return mBuffer.data();
    }

    const char* cbegin() const {
        return mBuffer.data();
    }

    const char* begin() const {
        return mBuffer.data();
    }

    char* begin() {
        return mBuffer.data();
    }

    const char* cend() const {
        return mBuffer.data() + mBuffer.size();
    }

    const char* end() const {
        return mBuffer.data() + mBuffer.size();
    }

    char* end() {
        return mBuffer.data() + mBuffer.size();
    }

    void clear() {
        mBuffer.clear();
    }

    void swap(String& rhs) noexcept {
        mBuffer.swap(rhs.mBuffer);
    }

    String& append(SizeType count, ValueType ch) {
        mBuffer.insert(mBuffer.end(), count, ch);
        return *this;
    }

    String& append(const String& str) {
        mBuffer.insert(mBuffer.end(), str.begin(), str.end());
        return *this;
    }

    String& append(const ValueType* cstr) {
        String str{cstr};
        return append(str);
    }

    String& operator+=(const String& str) {
        return append(str);
    }

    String& operator+=(const ValueType* cstr) {
        return append(cstr);
    }

    void resize(SizeType newSize, ValueType value = ValueType()) {
        mBuffer.resize(newSize);
    }
private:
    std::vector<ValueType> mBuffer;
};

bool operator==(const String& lhs, const String& rhs) {
    return lhs.size() == rhs.size() &&
        std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator<(const String& lhs, const String& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end());
}

} // namespace mdb

#endif // !STRING_HPP