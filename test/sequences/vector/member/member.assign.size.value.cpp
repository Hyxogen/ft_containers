// Simple tests for vector assign(size_type, const_reference)

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
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec;
                vec.assign(3, 42);
                assert(vec.size() == 3);
                assert(vec.capacity() >= 3);
                assert(vec[0] == 42);
                assert(vec[1] == 42);
                assert(vec[2] == 42);
        }
        {
                std::size_t instances = test::tracking_class::instances();
                ft::vector<test::tracking_class> vec(100);
                vec.assign(3, test::tracking_class());
                assert(test::tracking_class::instances() == instances + 3);
        }
        return 0;
}
