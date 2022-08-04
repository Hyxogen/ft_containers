// custom c++ integral_constant implementation

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
#ifndef INTEGRAL_CONSTANT_HPP
#define INTEGRAL_CONSTANT_HPP

namespace ft {

template <class T, T v> struct integral_constant {
        typedef T value_type;
        typedef integral_constant<T, v> type;
        static const T value = v;
        operator value_type() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;
} // namespace ft
#endif /* INTEGRAL_CONSTANT_HPP */
