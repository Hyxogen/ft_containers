// integral_constant tests

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
#include <typeinfo>

int main() {
    {
        typedef ft::integral_constant<int, 5> integral;
        integral v;
        assert(typeid(integral::value_type) == typeid(int));
        assert(typeid(integral::type) == typeid(integral));
        assert(integral::value == 5);
        assert(static_cast<int>(v) == 5);
    }
    {
        typedef ft::integral_constant<char, 42> integral;
        integral v;
        assert(typeid(integral::value_type) == typeid(char));
        assert(typeid(integral::type) == typeid(integral));
        assert(integral::value == 42);
        assert(static_cast<char>(v));
    }
    {
        ft::true_type t;
        assert(typeid(ft::true_type::value_type) == typeid(bool));
        assert(typeid(ft::true_type::type) ==
               typeid(ft::integral_constant<bool, true>));
        assert(ft::true_type::value);
        assert(static_cast<bool>(t));
    }
    {
        ft::false_type f;
        assert(typeid(ft::false_type::value_type) == typeid(bool));
        assert(typeid(ft::false_type::type) ==
               typeid(ft::integral_constant<bool, false>));
        assert(!ft::false_type::value);
        assert(!static_cast<bool>(f));
    }
    return 0;
}
