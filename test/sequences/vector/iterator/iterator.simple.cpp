// simple vector iterator tests

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
#include <cstddef>
#include <cassert>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec;
                assert(vec.begin() == vec.end());
        }
        {
                ft::vector<int> vec(3, 42);
                assert(vec.begin() != vec.end());
                std::size_t count = 0;
                for (ft::vector<int>::iterator it = vec.begin();
                     it != vec.end(); ++it) {
                        ++count;
                        assert(*it == 42);
                        *it /= 2;
                }
                assert(count == 3);
                for (ft::vector<int>::iterator it = vec.begin();
                     it != vec.end(); ++it) {
                        assert(*it == 21);
                }
        }
        {
                ft::vector<int> vec(5, 54321);
                assert(vec.begin() != vec.end());
                for (ft::vector<int>::const_iterator it = vec.begin();
                     it != vec.end(); ++it) {
                        assert(*it == 54321);
                }
        }
        return 0;
}
