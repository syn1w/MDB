// Simple dynamic string library.
// Using String instead of std::string for binary security.
#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <vector>

namespace mdb {

class String {
public:
    using SizeType = std::size_t;
    using ValueType = char;

public:
    String() : mBuffer() { }

    String(const void* data, SizeType len) 
        : mBuffer(static_cast<const ValueType*>(data),
                  static_cast<const ValueType*>(data) + len) {
    }

    String(const ValueType* str) : String(str, std::strlen(str)) { }

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

    const ValueType* c_str() const {
        return mBuffer.data();
    }

    const void* data() const {
        return mBuffer.data();
    }

private:
    std::vector<ValueType> mBuffer;
};

} // namespace mdb

#endif // !STRING_HPP