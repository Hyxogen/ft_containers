// simple iterator_traits tests

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
#include <cassert>
#include <iterator.hpp>
#include <iterator>
#include <typeinfo>

template <typename T> void test() {
        assert(typeid(typename ft::iterator_traits<T>::difference_type) ==
               typeid(typename std::iterator_traits<T>::difference_type));
        assert(typeid(typename ft::iterator_traits<T>::value_type) ==
               typeid(typename std::iterator_traits<T>::value_type));
        assert(typeid(typename ft::iterator_traits<T>::pointer) ==
               typeid(typename std::iterator_traits<T>::pointer));
        assert(typeid(typename ft::iterator_traits<T>::reference) ==
               typeid(typename std::iterator_traits<T>::reference));
        assert(typeid(typename ft::iterator_traits<T>::iterator_category) ==
               typeid(typename std::iterator_traits<T>::iterator_category));
}

int main() {
        test<int *>();
        test<const int*>();
}
