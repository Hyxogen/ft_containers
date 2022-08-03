// custom c++ stl vector implementation

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

#include <cstddef>
#include <memory>

namespace ft {

template <class T, typename Allocator = std::allocator<T> > class vector {
      public:
        typedef T value_type;
        typedef typename Allocator::reference reference;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
	
      private:
        value_type *_data;
        size_type _size;
	size_type _capacity;

        Allocator _allocator;

      public:
        vector() : _data(NULL), _size(0), _capacity(0) {}

        explicit vector(const Allocator &alloc)
		: _data(NULL), _size(0), _capacity(0), _allocator(alloc) {}
	
	explicit vector(size_type count, const T &value, const Allocator &alloc = Allocator())
		: _data(NULL), _size(0), _capacity(0), _allocator(alloc) {
		_data = _allocator.allocate(count);
		_size = count;
		_capacity = _size;
		for (size_type idx = 0; idx < _size; ++idx) {
			_data[idx] = T(value);
		}
	}

	reference operator[](size_type n) { return _data[n]; }
        size_type size() const { return _size; }
	size_type capacity() const { return _capacity; }
        bool empty() const { return _size == 0; }
};
} // namespace ft

#endif /* FT_VECTOR_HPP */
