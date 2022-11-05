// vector reverse iterator tests

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
#include <vector.hpp>

/* TODO write these tests with proper sequences */
int main() {
        {
                ft::vector<int> vec;
                assert(vec.rbegin() == vec.rend());
        }
        {
                ft::vector<int> vec(300, 42);
                assert(vec.rbegin() != vec.rend());
                std::size_t count = 0;
                for (ft::vector<int>::reverse_iterator it = vec.rbegin();
                     it != vec.rend(); ++it) {
                        ++count;
                        assert(*it == 42);
                        *it /= 2;
                }
                assert(count == 300);
                for (ft::vector<int>::reverse_iterator it = vec.rbegin();
                     it != vec.rend(); ++it) {
                        assert(*it == 21);
                }
        }
        {
                ft::vector<int> vec;
                vec.push_back(5);
                vec.push_back(11);
                vec.push_back(17);
                vec.push_back(21);

                ft::vector<int>::reverse_iterator it = vec.rbegin();
                assert(*it++ == 21);
                assert(*it++ == 17);
                assert(*it++ == 11);
                assert(*it++ == 5);
                assert(it == vec.rend());
        }
        return 0;
}
