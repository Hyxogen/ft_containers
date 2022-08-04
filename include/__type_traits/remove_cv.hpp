// custom c++ remove_cv implementation

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
#ifndef REMOVE_CV_HPP
#define REMOVE_CV_HPP

#include <__type_traits/remove_const.hpp>
#include <__type_traits/remove_volatile.hpp>

namespace ft {
template <class T> struct remove_cv {
        typedef typename ft::remove_const<
            typename ft::remove_volatile<T>::type>::type type;
};
} // namespace ft

#endif /* REMOVE_CV_HPP */
