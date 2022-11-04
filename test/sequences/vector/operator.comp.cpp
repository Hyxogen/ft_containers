// tests for vector comparison operators

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

int main() {
        ft::vector<int> vec1;
        ft::vector<int> vec2;
        ft::vector<int> vec3;

        vec1.push_back(1);
        vec1.push_back(2);
        vec1.push_back(3);

        vec2.push_back(7);
        vec2.push_back(8);
        vec2.push_back(9);
        vec2.push_back(10);

        vec3.push_back(1);
        vec3.push_back(2);
        vec3.push_back(3);

        assert(!(vec1 == vec2));
        assert(vec1 != vec2);
        assert(vec1 < vec2);
        assert(vec1 <= vec2);
        assert(!(vec1 > vec2));
        assert(!(vec1 >= vec2));

        assert(vec1 == vec3);
        assert(!(vec1 != vec3));
        assert(!(vec1 < vec3));
        assert(vec1 <= vec3);
        assert(!(vec1 > vec3));
        assert(vec1 >= vec3);
        return 0;
}
