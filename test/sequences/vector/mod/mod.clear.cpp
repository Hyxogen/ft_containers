// Simple vector clear tests

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
                ft::vector<int> vec(500, 500);
                ft::vector<int>::size_type capacity = vec.capacity();
                assert(vec.size() == 500);
                vec.clear();
                assert(vec.size() == 0);
                assert(vec.capacity() == capacity);
        }
        {
                std::size_t instances = test::tracking_class::instances();
                ft::vector<test::tracking_class> vec(42);
                assert(test::tracking_class::instances() == instances + 42);
                vec.clear();
                assert(test::tracking_class::instances() == instances);
        }
        return 0;
}
