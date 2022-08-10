// tests for vector(size_type n, const value_type &x) constructor

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
#include <cassert>
#include <classes.hpp>
#include <vector.hpp>

int main() {
        {
                ft::vector<int> vec(5, 42);
                assert(vec.size() == 5);
                assert(vec.capacity() >= 5);
                assert(vec[0] == 42);
                assert(vec[1] == 42);
                assert(vec[2] == 42);
                assert(vec[3] == 42);
                assert(vec[4] == 42);
        }
        {
                test::allocator_wrapper<int> alloc;
                std::size_t count = test::calls["copy"];
                ft::vector<int, test::allocator_wrapper<int> > vec(5, 42);
                assert(vec.size() == 5);
                assert(vec.capacity() >= 5);
                assert(vec[0] == 42);
                assert(vec[1] == 42);
                assert(vec[2] == 42);
                assert(vec[3] == 42);
                assert(vec[4] == 42);
                assert((test::calls["copy"] - count) == 1);
        }
        {
                test::throwing_class<int> clazz;
                std::size_t used = test::allocator_tracker<
                    test::throwing_class<int> >::mem_used();
                test::throwing_class<int>::make_next_throw();
                try {
                        ft::vector<
                            test::throwing_class<int>,
                            test::allocator_tracker<test::throwing_class<int> > >
                            vec(5, clazz);
			assert(false);
                } catch (const test::too_many_instantiations &ex) {
                        assert(test::allocator_tracker<
                                   test::throwing_class<int> >::mem_used()
                               == used);
                }
        }
        return 0;
}
