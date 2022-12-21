// is_integral tests

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
#include <string>
#include <type_traits.hpp>

int main() {
    assert(ft::is_integral<bool>::value);
    assert(ft::is_integral<char>::value);
    assert(ft::is_integral<signed char>::value);
    assert(ft::is_integral<unsigned char>::value);
    assert(ft::is_integral<short>::value);
    assert(ft::is_integral<unsigned short>::value);
    assert(ft::is_integral<int>::value);
    assert(ft::is_integral<unsigned int>::value);
    assert(ft::is_integral<long>::value);
    assert(ft::is_integral<unsigned long>::value);

    assert(ft::is_integral<const bool>::value);
    assert(ft::is_integral<const char>::value);
    assert(ft::is_integral<const signed char>::value);
    assert(ft::is_integral<const unsigned char>::value);
    assert(ft::is_integral<const short>::value);
    assert(ft::is_integral<const unsigned short>::value);
    assert(ft::is_integral<const int>::value);
    assert(ft::is_integral<const unsigned int>::value);
    assert(ft::is_integral<const long>::value);
    assert(ft::is_integral<const unsigned long>::value);

    assert(ft::is_integral<volatile bool>::value);
    assert(ft::is_integral<volatile char>::value);
    assert(ft::is_integral<volatile signed char>::value);
    assert(ft::is_integral<volatile unsigned char>::value);
    assert(ft::is_integral<volatile short>::value);
    assert(ft::is_integral<volatile unsigned short>::value);
    assert(ft::is_integral<volatile int>::value);
    assert(ft::is_integral<volatile unsigned int>::value);
    assert(ft::is_integral<volatile long>::value);
    assert(ft::is_integral<volatile unsigned long>::value);

    assert(ft::is_integral<const volatile bool>::value);
    assert(ft::is_integral<const volatile char>::value);
    assert(ft::is_integral<const volatile signed char>::value);
    assert(ft::is_integral<const volatile unsigned char>::value);
    assert(ft::is_integral<const volatile short>::value);
    assert(ft::is_integral<const volatile unsigned short>::value);
    assert(ft::is_integral<const volatile int>::value);
    assert(ft::is_integral<const volatile unsigned int>::value);
    assert(ft::is_integral<const volatile long>::value);
    assert(ft::is_integral<const volatile unsigned long>::value);

    assert(!ft::is_integral<int *>::value);
    assert(!ft::is_integral<float>::value);
    assert(!ft::is_integral<std::string>::value);
}
