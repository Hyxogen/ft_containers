// tests for equal(iter, iter, iter)

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
#include <algorithm.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <list>
#include <vector>

template <typename T, typename U> bool is_equal(const T &t, const U &u) {
        return ft::equal(t.begin(), t.end(), u.begin());
}

int main() {
        {
                const std::vector<int> vec;
                assert(is_equal(vec, vec));
        }
        {
                std::vector<int> vec(300);
                std::generate(vec.begin(), vec.end(), std::rand);
                assert(is_equal(vec, vec));
        }
        {
                std::vector<int> vec(300);
                std::generate(vec.begin(), vec.end(), std::rand);
                const std::list<int> list(vec.begin(), vec.end());
                assert(is_equal(vec, list));
        }
        {
                std::vector<int> vec1(300);
                std::generate(vec1.begin(), vec1.end(), std::rand);
                std::vector<int> vec2(vec1);
                if (vec2[152] > 500) {
                        vec2[152] -= 1;
                } else {
                        vec2[152] += 1;
                }
                assert(!is_equal(vec1, vec2));
        }
        return 0;
}
