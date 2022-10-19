// vector erase(iterator) tests

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
#include <string>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec;
                for (int i = 0; i < 10; ++i) {
                        vec.push_back(i);
                }
                const std::size_t cap = vec.capacity();
                assert(vec.capacity() == cap);
                assert(vec.size() == 10);
        }
        {
                ft::vector<int> vec;
                for (int i = 0; i < 10; ++i) {
                        vec.push_back(i);
                }
                const std::size_t cap = vec.capacity();
                ft::vector<int>::const_iterator it = vec.erase(vec.begin());
                assert(it == vec.begin());
                assert(vec.capacity() == cap);
                assert(vec.size() == 9);
                for (int i = 0; i < 9; ++i) {
                        assert(vec[static_cast<unsigned int>(i)] == (i + 1));
                }
        }
        {
                ft::vector<int> vec;
                for (int i = 0; i < 10; ++i) {
                        vec.push_back(i);
                }
                const std::size_t cap = vec.capacity();
                ft::vector<int>::const_iterator it
                    = vec.erase(vec.begin() + 9);
                assert(it == vec.begin() + 9);
                assert(vec.capacity() == cap);
                assert(vec.size() == 9);
                for (int i = 0; i < 9; ++i) {
                        assert(vec[static_cast<unsigned int>(i)] == i);
                }
        }
        {
                ft::vector<int> vec;
                for (int i = 0; i < 10; ++i) {
                        vec.push_back(i);
                }
                const std::size_t cap = vec.capacity();
                ft::vector<int>::const_iterator it
                    = vec.erase(vec.begin() + 5);
                assert(it == vec.begin() + 5);
                assert(vec.capacity() == cap);
                assert(vec.size() == 9);
                for (int i = 0; i < 9; ++i) {
                        assert(vec[static_cast<unsigned int>(i)]
                               == (i + (i >= 5)));
                }
        }
        {
                ft::vector<std::string> vec(100, "Hello There!");
                const std::size_t cap = vec.capacity();
                ft::vector<std::string>::const_iterator it
                    = vec.erase(vec.begin() + 67);
                assert(it == vec.begin() + 67);
                assert(vec.capacity() == cap);
                assert(vec.size() == 99);
                ft::vector<std::string>::iterator tmp = vec.begin();
                for (; tmp != vec.end(); ++tmp) {
                        assert(*tmp == "Hello There!");
                }
        }
        {
                typedef test::tracking_class clazz;
                ft::vector<clazz> vec(500);
                const std::size_t cap = vec.capacity();
                const std::size_t count = clazz::instances();
                ft::vector<clazz>::const_iterator it
                    = vec.erase(vec.begin() + 179);
                assert(it == vec.begin() + 179);
                assert(vec.capacity() == cap);
                assert(vec.size() == 499);
                assert(clazz::instances() == count - 1);
        }
        return 0;
}
