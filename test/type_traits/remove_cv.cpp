// remove_cv tests

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
        assert((!test<const volatile int, int>()));

        assert((test<ft::remove_cv<volatile int>::type, int>()));
	assert((test<ft::remove_cv<const int>::type, int>()));
        assert((test<ft::remove_cv<const volatile int>::type,
                     int>()));
	assert((test<ft::remove_cv<volatile const int>::type,
                     int>()));
        assert((test<ft::remove_cv<volatile int *volatile>::type,
                     volatile int *>()));
	assert((test<ft::remove_cv<volatile const int *volatile>::type,
                     volatile const int *>()));
	assert((test<ft::remove_cv<volatile const int *const volatile>::type,
                     volatile const int *>()));
        return 0;
}
