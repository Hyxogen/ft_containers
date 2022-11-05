// Custom c++ stl vector implementation

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
#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <algorithm.hpp>
#include <algorithm>
#include <cstddef>
#include <iterator.hpp>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits.hpp>

namespace ft {

template <typename Allocator> class vector_base {
      public:
        typedef typename Allocator::value_type value_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename Allocator::size_type size_type;
        typedef Allocator allocator_type;

      private:
        Allocator _alloc;

        size_type _capacity;
        pointer _data;

      protected:
        vector_base(const Allocator &alloc = Allocator())
            : _alloc(alloc), _capacity(0), _data(NULL) {}

        vector_base(size_type capacity, const Allocator &alloc)
            : _alloc(alloc), _capacity(capacity),
              _data(_alloc.allocate(_capacity)) {}

        vector_base(const vector_base &other)
            : _alloc(other._alloc), _capacity(other._capacity),
              _data(_alloc.allocate(_capacity)) {}

        ~vector_base() {
                if (_data != NULL) {
                        _alloc.deallocate(_data, _capacity);
                }
        }

      public:
        allocator_type get_allocator() const { return _alloc; }

        void swap(vector_base &other) {
                std::swap(_alloc, other._alloc);
                std::swap(_capacity, other._capacity);
                std::swap(_data, other._data);
        }

        void reserve(size_type new_cap) {
                if (new_cap <= capacity())
                        return;
                _data = _alloc.allocate(new_cap);
                _capacity = new_cap;
        }

        pointer data() { return _data; }
        const_pointer data() const { return _data; }
        size_type capacity() const { return _capacity; }
        iterator begin() { return data(); }
        iterator end() { return begin() + capacity(); }
        const_iterator begin() const { return data(); }
        const_iterator end() const { return begin() + capacity(); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const {
                return reverse_iterator(end());
        }
        const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
        }

        void destroy_at(pointer p) { _alloc.destroy(p); }

        void construct_at(pointer p, const_reference val) {
                _alloc.construct(p, val);
        }
};

template <class T, typename Allocator = std::allocator<T> >
class vector : public vector_base<Allocator> {
        typedef vector_base<Allocator> _base;

      public:
        typedef typename _base::value_type value_type;
        typedef typename _base::reference reference;
        typedef typename _base::pointer pointer;
        typedef typename _base::const_pointer const_pointer;
        typedef typename _base::const_reference const_reference;
        typedef typename _base::pointer iterator;
        typedef typename _base::const_pointer const_iterator;
        typedef typename _base::reverse_iterator reverse_iterator;
        typedef typename _base::const_reverse_iterator const_reverse_iterator;
        typedef typename _base::allocator_type allocator_type;
        typedef typename _base::size_type size_type;

      private:
        size_type _size;

      public:
        vector() : _base(), _size(0) {}

        explicit vector(const Allocator &alloc) : _base(alloc), _size(0) {}

        explicit vector(size_type count, const_reference value = T(),
                        const Allocator &alloc = Allocator())
            : _base(count, alloc), _size(count) {
                initialize_aux(count, value, ft::true_type());
        }

        template <class InputIt>
        vector(InputIt first, InputIt last,
               const Allocator &alloc = Allocator())
            : _base(alloc), _size(0) {
                typedef typename ft::is_integral<InputIt>::type Integral;
                initialize_aux(first, last, Integral());
        }

        vector(const vector &other) : _base(other), _size(other._size) {
                std::uninitialized_copy(other.begin(), other.end(), begin());
        }

      protected:
        vector(const vector &other, size_type capacity)
            : _base(capacity, other.get_allocator()),
              _size(other.size() < capacity ? other.size() : capacity) {
                if (capacity < other.size()) {
                        std::uninitialized_copy(
                            other.begin(), other.begin() + capacity, begin());
                } else {
                        std::uninitialized_copy(other.begin(), other.end(),
                                                begin());
                }
        }

      public:
        ~vector() { clear(); }

        reference operator[](size_type n) {
                return *(begin() + n);
        } /*TODO
            perhaps make this not use begin() */

        const_reference operator[](size_type n) const {
                return *(begin() + n);
        }

        reference at(size_type pos) {
                if (!(pos < size())) {
                        throw std::out_of_range(
                            "out of bounds access in vector::at");
                }
                return this->operator[](pos);
        }

        const_reference at(size_type pos) const {
                if (!(pos < size())) {
                        throw std::out_of_range(
                            "out of bounds access in vector::at");
                }
                return this->operator[](pos);
        }

        iterator begin() { return _base::begin(); }
        iterator end() { return begin() + size(); }
        const_iterator begin() const { return _base::begin(); }
        const_iterator end() const { return begin() + size(); }
        reverse_iterator rbegin() { return _base::rbegin(); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const { return _base::rbegin(); }
        const_reverse_iterator rend() const {
                return reverse_iterator(begin());
        }
        size_type size() const { return _size; }
        size_type capacity() const { return _base::capacity(); }
        bool empty() const { return _size == 0; }

        vector &operator=(const vector &other) {
                if (this != &other) {
                        vector tmp(other);
                        swap(tmp);
                }
                return *this;
        }

        size_type max_size() const {
                return std::numeric_limits<size_type>::max()
                       / sizeof(value_type);
        }

        void assign(size_type count, const_reference value) {
                clear();
                initialize_aux(count, value, ft::true_type());
        }

        template <typename InputIt> void assign(InputIt first, InputIt last) {
                clear();
                typedef typename ft::is_integral<InputIt>::type Integral;
                initialize_aux(first, last, Integral());
        }

        void push_back(const_reference value) {
                if (capacity() < size() + 1) {
                        grow_uninitialized(capacity() == 0 ? 1
                                                           : capacity() * 2);
                }
                _base::construct_at(end(), value);
                ++_size;
        }

        void pop_back() {
                _base::destroy_at(end() - 1);
                _size -= 1;
        }

        void swap(vector &other) {
                _base::swap(other);
                std::swap(_size, other._size);
        }

        void clear() {
                destroy(begin(), end());
                _size = 0;
        }

        template <typename InputIt>
        void insert(iterator pos, InputIt first, InputIt last) {
                typedef typename ft::is_integral<InputIt>::type Integral;
                insert_aux(pos, first, last, Integral());
        }

        void insert(iterator pos, size_type n, const T &value) {
                insert_aux(pos, n, value, ft::true_type());
        }

        iterator insert(iterator pos, const T &value) {
                const size_type offset = static_cast<size_type>(pos - begin());
                insert(pos, 1, value);
                return begin() + offset;
        }

        void reserve(size_type new_cap) {
                if (new_cap > max_size()) {
                        throw std::length_error(
                            "new_cap exceeds max_size() in vector::reserve");
                }
                if (new_cap <= capacity())
                        return;
                vector new_vec(*this, new_cap);
                swap(new_vec);
        }

        void resize(size_type count, T value = T()) {
                if (count > size()) {
                        insert(end(), count - size(), value);
                } else if (count < size()) {
                        erase(begin() + count, end());
                }
        }

        iterator erase(iterator position) {
                return erase(position, position + 1);
        }

        iterator erase(iterator first, iterator last) {
                iterator it(std::copy(last, end(), first));
                destroy(it, end());
                _size -= static_cast<size_type>(last - first);
                return first;
        }

      protected:
        void destroy(iterator first, iterator last) {
                for (; first != last; ++first) {
                        _base::destroy_at(first);
                }
        }

        void shrink(size_type count) {
                vector new_vec(*this, count);
                swap(new_vec);
        }

        void grow_uninitialized(size_type count) {
                vector new_vec(*this, count);
                swap(new_vec);
        }

        void grow_append(size_type count, const_reference value = T()) {
                vector new_vec(count, value);
                std::copy(begin(), end(), new_vec.begin());
                swap(new_vec);
        }

        template <typename Integer1, typename Integer2>
        void initialize_aux(Integer1 count, Integer2 value,
                            ft::true_type /*unused*/) {
                _size = static_cast<size_type>(count);
                _base::reserve(size());
                std::uninitialized_fill(begin(), end(), value);
        }

        template <typename InputIt>
        void initialize_aux(InputIt first, InputIt last,
                            ft::false_type /*unused*/) {
                initialize_range_aux(first, last,
                                     typename ft::iterator_traits<
                                         InputIt>::iterator_category());
        }

        template <typename InputIt>
        void initialize_range_aux(InputIt first, InputIt last,
                                  std::input_iterator_tag /*unused*/) {
                vector tmp; // TODO write test to check if allocation fails in
                            // the middle that the deconstructors of all the
                            // already constructed objects get called.
                for (; first != last; ++first) {
                        tmp.push_back(*first);
                }
                swap(tmp);
        }

        template <typename Iter>
        void initialize_range_aux(Iter first, Iter last,
                                  std::forward_iterator_tag /*unused*/) {
                _size = static_cast<size_type>(std::distance(first, last));
                _base::reserve(_size);
                std::uninitialized_copy(first, last, begin());
        }

        template <typename SizeType, typename ValueType>
        void insert_aux(iterator pos, SizeType n, ValueType value,
                        ft::true_type /*unused*/) {
                vector tmp(n, value);
                insert(pos, tmp.begin(), tmp.end());
        }

        template <typename InputIt>
        void insert_aux(iterator pos, InputIt first, InputIt last,
                        ft::false_type /*unused*/) {
                insert_range_aux(pos, first, last,
                                 typename ft::iterator_traits<
                                     InputIt>::iterator_category());
        }

        template <typename ForwardIt>
        void insert_range_aux(iterator pos, ForwardIt first, ForwardIt last,
                              std::forward_iterator_tag /*unused*/) {
                const size_type count
                    = static_cast<size_type>(std::distance(first, last));
                const size_type offset = static_cast<size_type>(pos - begin());

                reserve(size() + count);

                pos = begin() + offset;
                const size_type elements_after
                    = static_cast<size_type>(end() - pos);
                const iterator old_end = end();
                if (elements_after > count) {
                        std::uninitialized_copy(end() - count, end(), end());
                        _size += count;
                        std::copy_backward(pos, old_end - count, old_end);
                        std::copy(first, last, pos);
                } else {
                        const size_type difference = count - elements_after;
                        std::uninitialized_fill_n(end(), difference,
                                                  value_type());
                        _size += difference;
                        std::uninitialized_copy(pos, old_end, end());
                        _size += count - difference;
                        std::copy(first, last, pos);
                }
        }

        template <typename InputIt>
        void insert_range_aux(iterator pos, InputIt first, InputIt last,
                              std::input_iterator_tag /*unused*/) {
                vector tmp(first, last);
                insert(pos, tmp.begin(), tmp.end());
        }
};
template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc> &lhs,
                const ft::vector<T, Alloc> &rhs) {
        return lhs.size() == rhs.size()
               && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc> &lhs,
                const ft::vector<T, Alloc> &rhs) {
        return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc> &lhs,
               const ft::vector<T, Alloc> &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                           rhs.end());
}

template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc> &lhs,
                const ft::vector<T, Alloc> &rhs) {
        return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc> &lhs,
               const ft::vector<T, Alloc> &rhs) {
        return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc> &lhs,
                const ft::vector<T, Alloc> &rhs) {
        return !(lhs < rhs);
}
} // namespace ft
#endif /* FT_VECTOR_HPP */
