#ifndef COMPARE_HPP
#define COMPARE_HPP

#include <functional>

namespace test {

template <typename T> struct less : public std::binary_function<T, T, bool> {
    T v;
    less(T v) : v(v) {}

    bool operator==(const less &other) const { return v == other.v; }
    bool operator()(const T &lhs, T &rhs) const { return lhs < rhs; }
};
} // namespace test

#endif
