#include "String.hpp"

#include <cstdio>

namespace mdb {

namespace {

constexpr std::size_t kMaxNumberSize = 32;
constexpr std::array<char, 19> kDigits = {'9', '8', '7', '6', '5', '4', '3',
                                          '2', '1', '0', '1', '2', '3', '4',
                                          '5', '6', '7', '8', '9'};

template <typename T,
          typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
String::SizeType intToString(char* buf, T value) {
    const char* zero = kDigits.data() + 9;
    bool negative = value < 0;
    char* p = buf;
    do {
        int lp = static_cast<int>(value % 10);
        value /= 10;
        *p++ = zero[lp];
    } while (value);

    if (negative) {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

} // namespace

String::String(std::int64_t value) {
    char buf[kMaxNumberSize];
    SizeType len = intToString(buf, value);

    mBuffer = Container{buf, buf + len};
    mBuffer.emplace_back('\0');
}

String::String(double value) {
    std::array<char, 256> buf;
    buf.fill('\0');
    std::size_t len = std::snprintf(buf.data(), buf.size(), "%.17g", value);

    // Remove tailing zeros after '.'
    if (std::find(buf.begin(), buf.end(), '.') != buf.end()) {
        // assert iter != buf.rend()
        auto iter = buf.rbegin();
        for (; *iter == '0'; ++iter) {
            --len;
        }

        if (*iter == '.') {
            --len;
        }
    }

    mBuffer = Container{buf.data(), buf.data() + len};
    mBuffer.emplace_back('\0');
}

} // namespace mdb