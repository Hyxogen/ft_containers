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
        typedef std::size_t size_type;

      private:
        value_type *_data;
        size_type _size;

      public:
        vector() : _data(NULL), _size(0) {}

        size_type size() const { return _size; }
        bool empty() const { return _size == 0; }
};
} // namespace ft

#endif /* FT_VECTOR_HPP */
