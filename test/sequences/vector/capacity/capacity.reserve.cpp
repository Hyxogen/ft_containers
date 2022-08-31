// tests for vector reserve

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
#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <string>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec;
                assert(vec.capacity() == 0);
                vec.reserve(0);
                assert(vec.capacity() == 0);
        }
        {
                ft::vector<int> vec(20);
                std::size_t cap = vec.capacity();
                assert(cap >= 20);
                vec.reserve(10);
                assert(vec.capacity() == cap);
        }
        {
                ft::vector<std::string> vec(1, "Hello There");
                assert(vec.capacity() == 1);
                vec.reserve(100);
                assert(vec.capacity() == 100);
                assert(vec[0] == "Hello There");
        }
        {
                typedef test::limited_allocator<std::string> allocator;
                ft::vector<std::string, allocator> vec(3);
                assert(vec.capacity() == 3);
                vec[0] = "Well";
                vec[1] = "Hello";
                vec[2] = "There";
                allocator::set_limit(allocator::active() + 1);
                ASSERT_THROW(vec.reserve(10), std::bad_alloc);
                assert(vec.capacity() == 3);
                assert(vec[0] == "Well");
                assert(vec[1] == "Hello");
                assert(vec[2] == "There");
        }
        return 0;
}
