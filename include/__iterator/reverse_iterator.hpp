// custom implementation of reverse_iterator

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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <__iterator/iterator_traits.hpp>
#include <iterator>

namespace ft {

template <class Iterator>
class reverse_iterator
    : public std::iterator<
          typename iterator_traits<Iterator>::iterator_category,
          typename iterator_traits<Iterator>::value_type,
          typename iterator_traits<Iterator>::difference_type,
          typename iterator_traits<Iterator>::pointer,
          typename iterator_traits<Iterator>::reference> {

      protected:
        Iterator _current;

      public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::difference_type
            difference_type;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef typename iterator_traits<Iterator>::pointer pointer;

        reverse_iterator() : _current() {}
        explicit reverse_iterator(Iterator x) : _current(x) {}
        template <class U>
        reverse_iterator(const reverse_iterator<U> &u)
            : _current(u._current) {}

        Iterator base() const { return _current; }

        reference operator*() const {
                Iterator tmp = _current;
                return *--tmp;
        }

        pointer operator->() const { return &(operator*()); }

        reverse_iterator &operator++() {
                --_current;
                return *this;
        }

        reverse_iterator operator++(int) {
                reverse_iterator tmp = *this;
                --_current;
                return tmp;
        }

        reverse_iterator &operator--() {
                ++_current;
                return *this;
        }

        reverse_iterator operator--(int) {
                reverse_iterator tmp = *this;
                ++_current;
                return tmp;
        }

        reverse_iterator operator+(difference_type n) const {
                return reverse_iterator(_current - n);
        }

        reverse_iterator &operator+=(difference_type n) {
                _current -= n;
                return *this;
        }

        reverse_iterator operator-(difference_type n) const {
                return reverse_iterator(_current + n);
        }

        reverse_iterator &operator-=(difference_type n) {
                _current += n;
                return *this;
        }

        reference operator[](difference_type idx) const {
                return _current[-idx - 1];
        }
};

template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
        return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
        return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
        return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
        return lhs.base() <= rhs.base();
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs,
               const reverse_iterator<Iterator> &rhs) {
        return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs,
                const reverse_iterator<Iterator> &rhs) {
        return lhs.base() >= rhs.base();
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> &lhs,
          const reverse_iterator<Iterator> &rhs) {
        return rhs.base() - lhs.base();
}

template <class Iterator>
reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator> &x) {
        return reverse_iterator<Iterator>(x.base() - n);
}
}

#endif /* REVERSE_ITERATOR_HPP */
