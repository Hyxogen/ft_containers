// iterator test utilities

// Copyright (C) 2022 Daan Meijer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see
// <https://www.gnu.org/licenses/>.
#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator>

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

        input_iterator() : _current() {}

      public:
        typedef typename std::iterator_traits<Iterator>::reference reference;
        typedef typename std::iterator_traits<Iterator>::pointer pointer;

        input_iterator(const Iterator &other) : _current(other) {}

        input_iterator(const input_iterator &other)
            : _current(other._current) {}

        input_iterator &operator=(const input_iterator &other) {
                if (this != &other) {
                        _current = other._current;
                }
                return *this;
        }

        bool operator==(const input_iterator &other) {
                return _current == other._current;
        }

        bool operator!=(const input_iterator &other) {
                return _current != other._current;
        }

        reference operator*() const { return *_current; }

        pointer operator->() const { return &(operator*()); }

        input_iterator &operator++() {
                ++_current;
                return *this;
        }

        input_iterator operator++(int) {
                ++_current;
                return input_iterator();
        }
};
} /* namespace test */
#endif /* ITERATORS_HPP */
