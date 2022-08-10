// custom c++ remove_const implementation

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
#ifndef REMOVE_CONST_HPP
#define REMOVE_CONST_HPP

namespace ft {
template <typename T> struct remove_const { typedef T type; };

template <typename T> struct remove_const<const T> { typedef T type; };
} // namespace ft

#endif /* REMOVE_CONST_HPP */