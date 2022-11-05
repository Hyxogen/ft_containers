// vector front tests

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
        {
                ft::vector<int> vec;
                vec.push_back(1);
                vec.push_back(2);
                vec.push_back(3);
                assert(vec.front() == 1);
                vec.pop_back();
                assert(vec.front() == 1);
                vec.pop_back();
                assert(vec.front() == 1);
                vec[0] = 4;
                assert(vec.front() == 4);
        }
        return 0;
}
