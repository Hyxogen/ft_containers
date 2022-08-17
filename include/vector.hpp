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

#include <algorithm>
#include <cstddef>
#include <iterator.hpp>
#include <iterator>
#include <memory>
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

        void swap(vector_base &other) {
                std::swap(_alloc, other._alloc);
                std::swap(_capacity, other._capacity);
                std::swap(_data, other._data);
        }

        void reserve(size_type new_cap) {
                if (new_cap <= capacity())
                        return;
                //assert(_data == NULL); /* TODO remove */
                _data = _alloc.allocate(new_cap);
                _capacity = new_cap;
        }

        pointer data() { return _data; }
        const_pointer data() const { return _data; }
        size_type capacity() const { return _capacity; }
        iterator begin() { return data(); }
        const_iterator begin() const { return data(); }
        iterator end() { return begin() + capacity(); }
        const_iterator end() const { return begin() + capacity(); }
        
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

        ~vector() { clear(); }

        reference operator[](size_type n) {
                return *(begin() + n);
        } /*TODO
            perhaps make this not use begin() */
        iterator begin() { return _base::begin(); }
        iterator end() { return begin() + size(); }
        const_iterator begin() const { return _base::begin(); }
        const_iterator end() const { return begin() + size(); }
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

        void swap(vector &other) {
                _base::swap(other);
                std::swap(_size, other._size);
        }

        void clear() {
                destroy(begin(), end());
                _size = 0;
        }

        // TODO write resize tests
        void resize(size_type count) {
                if (count < capacity()) {
                        shrink(count);
                } else if (count > capacity()) {
                        grow_append(count, value_type());
                }
        }

      protected:
        void destroy(iterator first, iterator last) {
                for (; first != last; ++first) {
                        _base::destroy_at(first);
                }
        }

        void shrink(size_type count) {
                vector new_vec;
                new_vec.reserve(count);
                std::uninitialized_copy(begin(), begin() + count,
                                        new_vec.begin());
                swap(new_vec);
        }

        void grow_uninitialized(size_type count) {
                vector new_vec;
                new_vec.reserve(count);
                new_vec.assign(begin(), end());
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
                _base::reserve(count);
                _size = count;
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
                for (; first != last; ++first) {
                        push_back(*first);
                }
        }

        template <typename Iter>
        void initialize_range_aux(Iter first, Iter last,
                                  std::forward_iterator_tag /*unused*/) {
                _size = std::distance(first, last);
                _base::reserve(_size);
                std::uninitialized_copy(first, last, begin());
        }
};
} // namespace ft

#endif /* FT_VECTOR_HPP */
