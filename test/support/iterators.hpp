// <https://www.gnu.org/licenses/>.
#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator>
#include <stdexcept>

namespace test {
template <typename T> struct range_iterator {
    typedef T difference_type;
    typedef T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef std::random_access_iterator_tag iterator_category;

  private:
    value_type _value;

  public:
    range_iterator(T value) : _value(value) {}
    range_iterator(const range_iterator &other) : _value(other._value) {}

    ~range_iterator() {}

    range_iterator &operator=(const range_iterator &other) {
        if (this != &other) {
            _value = other._value;
        }
        return *this;
    }

    bool operator==(const range_iterator &other) const {
        return _value == other._value;
    }

    bool operator!=(const range_iterator &other) const {
        return !(*this == other);
    }

    bool operator>=(const range_iterator &other) const {
        return _value >= other._value;
    }

    bool operator<=(const range_iterator &other) const {
        return _value <= other._value;
    }

    bool operator>(const range_iterator &other) const {
        return !(*this <= other);
    }

    bool operator<(const range_iterator &other) const {
        return !(*this >= other);
    }

    range_iterator operator+(difference_type n) const {
        return range_iterator(_value + n);
    }

    range_iterator &operator+=(difference_type n) {
        _value += n;
        return *this;
    }

    range_iterator operator-(difference_type n) const {
        return range_iterator(_value - n);
    }

    range_iterator &operator-=(difference_type n) {
        _value -= n;
        return *this;
    }

    difference_type operator-(const range_iterator &other) const {
        return _value - other._value;
    }

    range_iterator &operator++() {
        ++_value;
        return *this;
    }

    range_iterator operator++(int) {
        range_iterator tmp(*this);
        ++_value;
        return tmp;
    }

    range_iterator &operator--() {
        --_value;
        return *this;
    }

    range_iterator operator--(int) {
        range_iterator tmp(*this);
        --_value;
        return tmp;
    }

    reference operator*() const { return _value; }

    reference operator->() const { return _value; }

    reference operator[](difference_type n) const { return _value + n; }
};

// TODO add a check that value is read only once
template <typename Iterator>
struct input_iterator
    : public std::iterator<
          std::input_iterator_tag,
          typename std::iterator_traits<Iterator>::value_type,
          typename std::iterator_traits<Iterator>::difference_type,
          typename std::iterator_traits<Iterator>::pointer,
          typename std::iterator_traits<Iterator>::reference> {

  protected:
    Iterator _current;
    mutable bool _read;

    input_iterator() : _current() {}

  public:
    typedef typename std::iterator_traits<Iterator>::reference reference;
    typedef typename std::iterator_traits<Iterator>::pointer pointer;

    input_iterator(const Iterator &other) : _current(other), _read(false) {}

    input_iterator(const input_iterator &other)
        : _current(other._current), _read(other._read) {}

    input_iterator &operator=(const input_iterator &other) {
        if (this != &other) {
            _current = other._current;
            _read = other._read;
        }
        return *this;
    }

    bool operator==(const input_iterator &other) {
        return _current == other._current;
    }

    bool operator!=(const input_iterator &other) {
        return _current != other._current;
    }

    reference operator*() const {
        if (_read) {
            throw std::logic_error(
                "reading more than once from an input iterator");
        }
        _read = true;
        return *_current;
    }

    pointer operator->() const {
        if (_read) {
            throw std::logic_error(
                "reading more than once from an input iterator");
        }
        _read = true;
        return &(operator*());
    }

    input_iterator &operator++() {
        ++_current;
        _read = false;
        return *this;
    }

    input_iterator operator++(int) {
        ++_current;
        _read = false;
        return input_iterator();
    }
};
} /* namespace test */
#endif /* ITERATORS_HPP */
