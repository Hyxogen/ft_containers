// vector at tests

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
#include <assert.hpp>
#include <stdexcept>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec;
                ASSERT_THROW(vec.at(0), std::out_of_range);
        }
        {
                const ft::vector<int> vec;
                ASSERT_THROW(vec.at(0), std::out_of_range);
        }
        {
                ft::vector<int> vec(300, 42);
                for (unsigned int idx = 0; idx < 300; ++idx) {
                        assert(vec.at(idx) == 42);
                        ASSERT_THROW(vec.at(300 + idx), std::out_of_range);
                }
        }
        {
                const ft::vector<int> vec(300, 42);
                for (unsigned int idx = 0; idx < 300; ++idx) {
                        assert(vec.at(idx) == 42);
                        ASSERT_THROW(vec.at(300 + idx), std::out_of_range);
                }
        }
        {
                ft::vector<int> vec;
                for (int idx = 0; idx < 300; ++idx) {
                        vec.push_back(idx);
                }
                for (unsigned int idx = 0; idx < 300; ++idx) {
                        assert(vec.at(idx) == static_cast<int>(idx));
                }
        }
        {
                ft::vector<int> vec;
                for (int idx = 0; idx < 300; ++idx) {
                        vec.push_back(idx);
                }
                for (unsigned int idx = 0; idx < 300; ++idx) {
                        assert(vec.at(idx) == static_cast<int>(idx));
                }
        }
        {
                ft::vector<int> tmp;
                for (int idx = 0; idx < 300; ++idx) {
                        tmp.push_back(idx);
                }
                const ft::vector<int> vec(tmp);
                for (unsigned int idx = 0; idx < 300; ++idx) {
                        assert(vec.at(idx) == static_cast<int>(idx));
                }
        }
        return 0;
}
