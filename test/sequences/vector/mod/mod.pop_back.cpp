// vector::pop_back tests

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
#include <classes.hpp>
#include <cstddef>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec(1);

                vec.pop_back();
                assert(vec.size() == 0);
                assert(vec.capacity() == 1);
        }
        {
                ft::vector<int> vec;
                vec.reserve(2);

                vec.push_back(42);
                vec.push_back(21);

                const ft::vector<int>::iterator it = vec.begin();
                vec.pop_back();
                assert(vec.size() == 1);
                assert(vec[0] == 42);
                assert(vec.begin() == it);
        }
        {
                typedef test::tracking_class clazz;
                ft::vector<clazz> vec(30);

                const std::size_t count = clazz::instances();
                vec.pop_back();
                assert(clazz::instances() == count - 1);
                vec.pop_back();
                assert(clazz::instances() == count - 2);
        }
        {
                ft::vector<int> vec(100);

                for (size_t idx = 0; idx < 100; ++idx) {
                        assert(vec.size() == 100 - idx);
                        vec.pop_back();
                        assert(vec.size() == 99 - idx);
                }
        }
        return 0;
}
