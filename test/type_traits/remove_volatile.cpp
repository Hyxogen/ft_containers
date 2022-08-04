// remove_volatile tests

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
#include <type_traits.hpp>

namespace {
template <typename A, typename B> struct is_same : ft::false_type {};

template <typename A> struct is_same<A, A> : ft::true_type {};

template <typename A, typename B> bool test() { return is_same<A, B>::value; }
} // namespace

int main() {
        assert((test<int, int>()));
        assert((!test<volatile int, int>()));

        assert((test<typename ft::remove_volatile<volatile int>::type, int>()));
        assert((test<typename ft::remove_volatile<const volatile int>::type,
                     const int>()));
        assert((test<typename ft::remove_volatile<volatile const int>::type,
                     const int>()));
        assert((test<typename ft::remove_volatile<volatile int *volatile>::type,
                     volatile int *>()));
	assert((test<typename ft::remove_volatile<volatile const int *volatile>::type,
                     volatile const int *>()));
        return 0;
}
