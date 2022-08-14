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
template <class T, class Allocator> class vector_alloc_holder {
      public:
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::size_type size_type;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

      protected:
        pointer _begin, _end;
        Allocator _alloc;

      public:
        vector_alloc_holder() : _begin(NULL), _end(NULL), _alloc() {}

        vector_alloc_holder(const Allocator &alloc)
            : _begin(NULL), _end(NULL), _alloc(alloc) {}

        vector_alloc_holder(size_type n, const Allocator &alloc = Allocator())
                : _begin(NULL), _end(NULL), _alloc(alloc) {
                allocate(n);
        }

        ~vector_alloc_holder() {
                if (_begin != NULL) {
                        Allocator().deallocate(_begin, capacity());
                }
        }

        size_type capacity() const {
                return size_type(end() - begin());
        }

        iterator begin() {
                return _begin;
        };

        iterator end() {
                return _end;
        };

        const_iterator begin() const {
                return _begin;
        }

        const_iterator end() const {
                return _end;
        }

        void allocate(size_type n) {
                _begin = _alloc.allocate(n);
                _end = _begin + n;
        }

        void swap(vector_alloc_holder &other) {
                std::swap(_begin, other._begin);
                std::swap(_end, other._end);
                std::swap(_alloc, other._alloc);
        }
};

template <class T, typename Allocator = std::allocator<T> >
class vector {
        typedef vector_alloc_holder<T, Allocator> holder_type;
        
      public:
        typedef T value_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::const_reference const_reference;
        typedef pointer iterator;
        typedef const_pointer const_iterator;
        typedef Allocator allocator_type;
        typedef typename Allocator::size_type size_type;

      private:
        size_type _size;
        holder_type _holder;

      public:
        vector() : _size(0), _holder() {}

        explicit vector(const Allocator &alloc) : _size(0), _holder(alloc) {}

        explicit vector(size_type count, const_reference value = T(),
                        const Allocator &alloc = Allocator())
            : _size(count), _holder(count, alloc) {
                initialize_aux(count, value, ft::true_type());
        }

        template <class InputIt>
        vector(InputIt first, InputIt last,
               const Allocator &alloc = Allocator())
                : _size(0), _holder(alloc) {
                typedef typename ft::is_integral<InputIt>::type Integral;
                initialize_aux(first, last, Integral());
        }

        vector(const vector &other) : _size(other._size), _holder(_size) {
                std::uninitialized_copy(other.begin(), other.end(),
                                        begin());
        }

        ~vector() { clear(); }

        reference operator[](size_type n) {
                return *(begin() + n);
        } /*TODO
            perhaps make this not use begin() */
        iterator begin() { return _holder.begin(); }
        iterator end() { return begin() + size(); }
        const_iterator begin() const { return _holder.begin(); }
        const_iterator end() const { return begin() + size(); }
        size_type size() const { return _size; }
        size_type capacity() const { return _holder.capacity(); }
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
                        grow_uninitialized(capacity() == 0 ? 1 : capacity() * 2);
                }
                Allocator().construct(begin() + _size, value);
                ++_size;
        }

        void swap(vector &other) {
                _holder.swap(other._holder);
                std::swap(_size, other._size);
        }

        void clear() {
                destroy(begin(), end());
                _size = 0;
        }

        void resize(size_type count) {
                if (count < capacity()) {
                        shrink(count);
                } else if (count > capacity()) {
                        grow_append(count, value_type());
                }
        }

      protected:
        void destroy(iterator first, iterator last) {
                Allocator alloc;
                for (; first != last; ++first) {
                        alloc.destroy(first);
                }
        }

        void shrink(size_type count) {
                holder_type new_holder(count);
                std::uninitialized_copy(begin(), end(), new_holder.begin());
                destroy(begin() + count, end());
                _holder.swap(new_holder);
                _size = count;
        }

        typename holder_type::iterator grow_uninitialized(size_type count) {
                holder_type new_holder(count);
                typename holder_type::iterator it = std::uninitialized_copy(
                    begin(), end(), new_holder.begin());
                destroy(begin(), end());
                _holder.swap(new_holder);
                return it;
        }

        void grow_append(size_type count, const_reference value = T()) {
                holder_type new_holder(count);
                typename holder_type::iterator it = std::uninitialized_copy(
                    begin(), end(), new_holder.begin());
                std::uninitialized_fill(it, new_holder.end(), value);
                destroy(begin(), end());
                _holder.swap(new_holder);
                _size = count;
        }

        template <typename Integer1, typename Integer2>
        void initialize_aux(Integer1 count, Integer2 value,
                            ft::true_type /*unused*/) {
                _holder.allocate(count);
                _size = count;
                std::uninitialized_fill(begin(), end(), value);
        }

        template <typename InputIt>
        void initialize_aux(InputIt first, InputIt last,
                            ft::false_type /*unused*/) {
                initialize_range_aux(
                    first, last,
                    typename ft::iterator_traits<InputIt>::iterator_category());
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
                _holder.allocate(std::distance(first, last));
                std::uninitialized_copy(first, last, begin());
        }
};
} // namespace ft

#endif /* FT_VECTOR_HPP */
