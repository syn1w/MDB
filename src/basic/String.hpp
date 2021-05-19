// Simple dynamic string library.
// Using String instead of std::string for binary security.
#ifndef MDB_BASIC_STRING_HPP
#define MDB_BASIC_STRING_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "Allocator.hpp"
#include "RefCountBase.hpp"

namespace mdb {

class String : public RefCountBase {
public:
    using SizeType = std::size_t;
    using ValueType = char;

public:
    static const SizeType npos = static_cast<SizeType>(-1);

public:
    String() : mBuffer(1) {
        mBuffer[0] = '\0';
    }

    String(const void* data, SizeType len)
        : mBuffer(static_cast<const ValueType*>(data),
                  static_cast<const ValueType*>(data) + len) {
        mBuffer.push_back('\0');
    }

    String(const ValueType* str) : String(str, std::strlen(str)) {
    }

    String(std::int64_t value);
    String(double value);

    String(const String&) = default;
    String(String&&) noexcept = default;

    String& operator=(const String&) = default;
    String& operator=(String&&) noexcept = default;

    String& operator=(const ValueType* str) {
        return assign(str);
    }

    String& assign(const ValueType* str) {
        SizeType strLen = std::strlen(str) + 1;
        mBuffer.assign(str, str + strLen);
        return *this;
    }

    String& assign(const void* str, SizeType len) {
        mBuffer.assign(static_cast<const ValueType*>(str),
                       static_cast<const ValueType*>(str) + len);
        mBuffer.push_back('\0');
        return *this;
    }

    ~String() noexcept = default;

    SizeType size() const {
        return mBuffer.size() - 1;
    }

    SizeType length() const {
        return size();
    }

    bool isEmpty() const {
        return size() == 0;
    }

    SizeType capacity() const {
        return mBuffer.capacity();
    }

    ValueType& operator[](SizeType pos) {
        assert(pos <= size());
        return mBuffer.data()[pos];
    }

    const ValueType& operator[](SizeType pos) const {
        assert(pos <= size());
        return mBuffer.data()[pos];
    }

    const ValueType* cstr() const {
        return mBuffer.data();
    }

    const void* data() const {
        return mBuffer.data();
    }

    const ValueType* cbegin() const {
        return mBuffer.data();
    }

    const ValueType* begin() const {
        return mBuffer.data();
    }

    ValueType* begin() {
        return mBuffer.data();
    }

    const ValueType* cend() const {
        return mBuffer.data() + size();
    }

    const ValueType* end() const {
        return mBuffer.data() + size();
    }

    ValueType* end() {
        return mBuffer.data() + size();
    }

    void clear() {
        mBuffer.clear();
        mBuffer.emplace_back('\0');
    }

    void swap(String& rhs) noexcept {
        mBuffer.swap(rhs.mBuffer);
    }

    String& append(SizeType count, ValueType ch) {
        mBuffer.insert(std::prev(mBuffer.end()), count, ch);
        return *this;
    }

    String& append(const String& str) {
        mBuffer.insert(std::prev(mBuffer.end()), str.begin(), str.end());
        return *this;
    }

    String& append(const ValueType* cstr) {
        String str{cstr};
        return append(str);
    }

    String& append(const void* data, SizeType len) {
        String str{data, len};
        return append(str);
    }

    String& appendArgs() {
        return *this;
    }

    template <typename First, typename... Rest>
    String& appendArgs(First&& first, Rest&&... rest) {
        std::stringstream ss;
        ss << std::forward<First>(first);
        std::string str;
        ss >> str;
        append(str.c_str(), str.size());
        return appendArgs(std::forward<Rest>(rest)...);
    }

    String& appendVaList(const char* fmt, std::va_list ap) {
        static const SizeType kSmallBufLen = 1024;
        ValueType sbuf[kSmallBufLen];

        std::va_list cpy;
        va_copy(cpy, ap);
        int rlen = std::vsnprintf(sbuf, kSmallBufLen, fmt, cpy);
        assert(rlen >= 0);
        if (rlen < static_cast<int>(kSmallBufLen)) {
            append(sbuf, rlen);
            return *this;
        }

        // larger buffer
        ValueType* buf = reinterpret_cast<ValueType*>(
            ::operator new(sizeof(ValueType) * (rlen + 1)));

        std::vsnprintf(buf, static_cast<SizeType>(rlen), fmt, ap);
        append(buf, rlen);
        ::operator delete(buf);

        return *this;
    }

    String& appendFmtStr(const char* fmt, ...) {
        std::va_list ap;
        va_start(ap, fmt);
        appendVaList(fmt, ap);
        va_end(ap);
        return *this;
    }

    String substr(SizeType pos = 0, SizeType count = npos) {
        if (count == npos) {
            count = size() - pos;
        }
        assert(pos < size() && "string index out of range");
        assert(pos + count <= size() && "string index out of range");

        return String{cstr() + pos, count};
    }

    void toLower() {
        for (auto& ch : mBuffer) {
            ch = std::tolower(ch);
        }
    }

    void toUpper() {
        for (auto& ch : mBuffer) {
            ch = std::toupper(ch);
        }
    }

    String& operator+=(const String& str) {
        return append(str);
    }

    String& operator+=(const ValueType* cstr) {
        return append(cstr);
    }

    void resize(SizeType newSize, ValueType value = ValueType()) {
        mBuffer.resize(newSize + 1, value);
        mBuffer[newSize] = '\0';
    }

private:
    using Container = std::vector<ValueType, Allocator<ValueType>>;

    Container mBuffer;
};

inline bool operator==(const String& lhs, const String& rhs) {
    return lhs.size() == rhs.size() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

inline bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

inline bool operator<(const String& lhs, const String& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
}

inline bool operator>(const String& lhs, const String& rhs) {
    return rhs < lhs;
}

inline bool operator<=(const String& lhs, const String& rhs) {
    return !(rhs < lhs);
}

inline bool operator>=(const String& lhs, const String& rhs) {
    return !(lhs < rhs);
}

struct HashString {
    std::size_t operator()(const String& str) const {
        std::size_t result = 2166136261U;
        for (std::size_t i = 0; i < str.size(); ++i) {
            result ^= static_cast<std::size_t>(str[i]);
            result *= 16777619U;
        }

        return result;
    }
};

} // namespace mdb

#endif // !MDB_BASIC_STRING_HPP