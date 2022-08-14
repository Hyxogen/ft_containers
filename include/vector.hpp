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

// vector_base
//
// The reason I created a vector base is to have a central place for memory
// management. This means that vector itself doesn't have to deal with memory
// allocation and deallocation, all that is done this class. This improves
// readability, not cluttering the vector class with try-catch statements. This
// design choice was inspired by EASTL At first I didn't really get why one
// would do this, but now I do, and I'll try to explain it briefly here.
// Consider the case where, for example, a vector is created using the
// vector(size_type n, const value_type &x) constructor. This would first
// allocate enough storage to store _n_ times the value _x_, and then it would
// assign each one of them to a copy of x.  This is, however, not guaranteed to
// not throw an exception, and in the case that it does, we should free up our
// allocated memory and then return control to the calling function. You might
// already see here the problem that arises. At multiple places in the I would
// have to place something like this:
// try {
//  _data[idx] = x;
// } catch (const std::exception &ex) {
//  _clean up allocations_
// }
// This can be solved with a clever trick which is guaranteed by the
// C++ standard
//
// (ISO/IEC 14882:1998 15.2.2)
//   An object that is partially constructed or partially destroyed will have
//   destructors executed for all of its fully constructed subobjects, that is,
//   for subobjects for which the constructor has completed execution and the
//   destructor has not yet begun execution...
//
// (ISO/IEC 14882:1998 15.3.11)
//   The fully constructed base classes and members of an object shall be
//   destroyed before entering the handler of a function-try-block of a
//   constructor or destructor for that object.
//
// With this guarantee, I places the deallocation code in the
// vector_base deconstructor, ensuring that when the assignment throws
// an exception, there are no memory leaks.
//
//
// Acknowledgements
// I did not come up with this design by myself. I found it when I was
// scrolling around the source code of the EASTL (the STL library of
// EA). I found EASTL to be a good reference, since the code is not
// too complex, like libcxx form llvm or the gcc libstd++-v3. One can
// find the source code on github if you search for EASTL

template <class T, class Allocator> class vector_base {
      public:
        typedef T value_type;
        typedef T &reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::const_reference const_reference;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

      protected:
        pointer _data;
        size_type _capacity;

        Allocator _allocator;

      public:
        vector_base() : _data(NULL), _capacity(0) {}

        explicit vector_base(const Allocator &alloc)
            : _data(NULL), _capacity(0), _allocator(alloc) {}

        explicit vector_base(size_type count,
                             const Allocator &alloc = Allocator())
            : _data(NULL), _capacity(0), _allocator(alloc) {
                _data = _allocator.allocate(count);
                _capacity = count;
        }

        vector_base(const vector_base &other) : _data(NULL), _capacity(0) {
                resize(other._capacity);
        }

        virtual ~vector_base() { free_resources(); }

        size_type capacity() const { return _capacity; }
        pointer data() { return _data; }
        const_pointer data() const { return _data; }

        void swap(vector_base &other) {
                std::swap(_data, other._data);
                std::swap(_capacity, other._capacity);
                std::swap(_allocator, other._allocator);
        }

      protected:
        void resize(size_type new_capacity) {
                pointer tmp = _allocator.allocate(new_capacity);
                std::uninitialized_copy(begin(), end(), tmp);
                free_resources();
                _data = tmp;
                _capacity = new_capacity;
        }

        void grow_if_too_small(size_type capacity) {
                size_type new_capacity = _capacity;
                while (new_capacity < capacity) {
                        new_capacity = (new_capacity + 1) * 2;
                }
                if (new_capacity != _capacity) {
                        resize(new_capacity);
                }
        }

        iterator begin() { return data(); }
        iterator end() { return data() + capacity(); }
        const_iterator begin() const { return data(); }
        const_iterator end() const { return data() + capacity(); }

        void free_resources() {
                if (data() != NULL) {
                        _allocator.deallocate(data(), capacity());
                        _capacity = 0;
                }
        }
};

template <class T, typename Allocator = std::allocator<T> >
class vector : public vector_base<T, Allocator> {
        typedef vector_base<T, Allocator> _base;

      public:
        typedef typename _base::value_type value_type;
        typedef typename _base::reference reference;
        typedef typename _base::pointer pointer;
        typedef typename _base::const_pointer const_pointer;
        typedef typename _base::const_reference const_reference;
        typedef typename _base::iterator iterator;
        typedef typename _base::const_iterator const_iterator;
        typedef typename _base::allocator_type allocator_type;
        typedef typename _base::size_type size_type;

      private:
        size_type _size;

      public:
        vector() : _base(), _size(0) {}

        explicit vector(const Allocator &alloc) : _base(alloc), _size(0) {}

        explicit vector(size_type count, const_reference value = T(),
                        const Allocator &alloc = Allocator())
            : _base(count, alloc), _size(0) {
                _size = count;
                std::uninitialized_fill_n(begin(), count, value);
        }

        template <class InputIt>
        vector(typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                      InputIt>::type first,
               InputIt last, const Allocator &alloc = Allocator())
            : _base(alloc), _size(this->_capacity) {
                fill_iter(first, last,
                          typename ft::iterator_traits<
                              InputIt>::iterator_category());
        }

        vector(const vector &other) : _base(other), _size(other._size) {
                std::uninitialized_copy(other.begin(), other.end(),
                                        this->data());
        }

        ~vector() {
                for (iterator it = begin(); it != end(); ++it) {
                        this->_allocator.destroy(it);
                }
        }

        reference operator[](size_type n) { return this->_data[n]; }
        iterator begin() { return this->_data; }
        iterator end() { return this->_data + _size; }
        const_iterator begin() const { return this->_data; }
        const_iterator end() const { return this->_data + _size; }
        size_type size() const { return _size; }
        bool empty() const { return _size == 0; }

        vector &operator=(const vector &other) {
                if (this != &other) {
                        vector tmp(other);
                        swap(tmp);
                }
                return *this;
        }
        
        void push_back(const_reference value) {
                _base::grow_if_too_small(size() + 1);
                this->_allocator.construct(&this->_data[_size], value);
                ++_size;
        }

        void swap(vector &other) {
                _base::swap(other);
                std::swap(_size, other._size);
        }
        
      protected:
        template <class Iter>
        void fill_iter(Iter first, Iter last,
                       std::input_iterator_tag /*unused*/) {
                for (; first != last; ++first) {
                        push_back(*first);
                }
        }

        template <class iter>
        void fill_iter(iter first, iter last,
                       std::forward_iterator_tag /*unused*/) {
                _base::resize(std::distance(first, last));
                std::uninitialized_copy(first, last, begin());
        }
};
} // namespace ft

#endif /* FT_VECTOR_HPP */
