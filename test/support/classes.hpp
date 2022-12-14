#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <ostream>
#include <stdexcept>
#include <string>

namespace test {

struct too_many_instantiations : public std::logic_error {
    too_many_instantiations(const std::string &what) : logic_error(what) {}
};

template <typename T> class throwing_class {
    static long _throw_after;

    T _data;

  public:
    throwing_class() { check(); }

    explicit throwing_class(const T &data) : _data(data) { check(); }

    throwing_class(const throwing_class &other) : _data(other._data) {
        check();
    }

    ~throwing_class() {}

    static void reset() { _throw_after = -1; }

    static void make_next_throw() { _throw_after = 0; }

    static void throw_after(long instantiations) {
        _throw_after = instantiations;
    }

    throwing_class &operator=(const throwing_class &other) {
        if (this != &other) {
            _data = other._data;
            check();
        }
        return *this;
    }

    bool operator==(const T &data) const { return _data == data; }

    bool operator!=(const T &data) const { return !(_data == data); }

    bool operator==(const throwing_class &other) const {
        return _data == other._data;
    }

    bool operator!=(const throwing_class &other) const {
        return _data != other._data;
    }

    bool operator>(const throwing_class &other) const {
        return _data > other._data;
    }

    bool operator>=(const throwing_class &other) const {
        return _data >= other._data;
    }

    bool operator<(const throwing_class &other) const {
        return _data < other._data;
    }

    bool operator<=(const throwing_class &other) const {
        return _data <= other._data;
    }

    throwing_class &operator++() {
        ++_data;
        return *this;
    }

    throwing_class &operator--() {
        --_data;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &stream,
                                    const throwing_class &clazz) {
        return stream << clazz._data;
    }

  private:
    static void check() {
        if (_throw_after == 0) {
            throw too_many_instantiations("too many instantions of type");
        } else if (_throw_after > 0) {
            _throw_after -= 1;
        }
    }
};

template <typename T> long throwing_class<T>::_throw_after = -1;

template <typename T = int> class __tracking_class {
    static std::size_t _instances;

    T _value;

  public:
    __tracking_class() : _value() { _instances += 1; }

    __tracking_class(const T value) : _value(value) { _instances += 1; }

    __tracking_class(const __tracking_class &other) : _value(other._value) {
        _instances += 1;
    }

    ~__tracking_class() { _instances -= 1; }

    static std::size_t instances() { return _instances; }

    __tracking_class &operator=(const __tracking_class &) { return *this; }
    bool operator>(const __tracking_class &other) const {
        return _value > other._value;
    }

    bool operator>=(const __tracking_class &other) const {
        return _value >= other._value;
    }

    bool operator<(const __tracking_class &other) const {
        return _value < other._value;
    }

    bool operator<=(const __tracking_class &other) const {
        return _value <= other._value;
    }

    bool operator==(const __tracking_class &other) const {
        return _value == other._value;
    }

    bool operator!=(const __tracking_class &other) const {
        return _value != other._value;
    }

    __tracking_class &operator++() {
        ++_value;
        return *this;
    }

    __tracking_class &operator--() {
        --_value;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &stream,
                                    const __tracking_class<T> &clazz) {
        return stream << clazz._value;
    }
};

template <typename T> class compare_class {

    T _data;

  public:
    compare_class(const T &data = T()) : _data(data) {}
    compare_class(const compare_class &other) : _data(other._data) {}

    compare_class &operator=(const compare_class &other) {
        if (this != &other) {
            _data = other._data;
        }
        return *this;
    }

    bool operator<(const compare_class &other) const {
        return _data < other._data;
    }

    bool operator>(const compare_class &other) const {
        return _data > other._data;
    }

    friend std::ostream &operator<<(std::ostream &stream,
                                    const compare_class &clazz) {
        return stream << clazz._data;
    }
};

typedef __tracking_class<int> tracking_class;

template <typename T> std::size_t __tracking_class<T>::_instances = 0;
} // namespace test

#endif /* CLASSES_HPP */
