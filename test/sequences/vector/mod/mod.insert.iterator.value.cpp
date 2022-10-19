// vector::insert(const_iterator, value_type) tests

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
#include <classes.hpp>

int main() {
        {
                ft::vector<int> vec;
                vec.insert(vec.begin(), 42);
                assert(vec.size() == 1);
                assert(vec.capacity() >= 1);
                assert(vec[0] == 42);
        }
        {
                ft::vector<int> vec;
                vec.push_back(1);
                vec.push_back(2);
                vec.push_back(3);
                vec.insert(vec.begin() + 1, 12);
                assert(vec[1] == 12);
                assert(vec.size() == 4);
                assert(vec.capacity() >= 4);
        }
        {
                ft::vector<int> vec;
                vec.push_back(1);
                vec.push_back(2);
                vec.push_back(3);
                vec.insert(vec.end() - 1, 12);
                assert(vec[2] == 12);
        }
        {
                typedef ft::vector<std::string>::iterator iterator;
                ft::vector<std::string> vec;
                vec.reserve(7);
                vec.push_back("It's");
                vec.push_back("noon");
                vec.push_back("somewhere");
                vec.push_back("in");
                vec.push_back("world");
                const iterator it = vec.begin();

                iterator ret = vec.insert(vec.begin() + 4, "the");
                assert(ret == it + 4);
                assert(vec.begin() == it);
                assert(vec[4] == "the");
                assert(vec.size() == 6);
                assert(vec.capacity() == 7);

                ret = vec.insert(it + 1, "high");
                assert(it == vec.begin());
                assert(ret == it + 1);
                assert(vec.size() == 7);
                assert(vec.capacity() == 7);

                vec.insert(vec.end() - 1, "!");
                assert(vec.size() == 8);
                assert(vec.capacity() >= 8);
        }
        {
                typedef test::limited_allocator<std::string> allocator;
                typedef ft::vector<std::string, allocator>::iterator iterator;
                ft::vector<std::string, allocator> vec;
                vec.reserve(8);
                vec.push_back("Inserts");
                vec.push_back("elements");
                vec.push_back("at");
                vec.push_back("the");
                vec.push_back("location");
                vec.push_back("in");
                vec.push_back("the");
                vec.push_back("container");
                iterator it = vec.begin();

                allocator::set_limit(allocator::active());
                ASSERT_THROW(vec.insert(vec.begin() + 4, "specified"),
                             std::bad_alloc);
                assert(*it++ == "Inserts");
                assert(*it++ == "elements");
                assert(*it++ == "at");
                assert(*it++ == "the");
                assert(*it++ == "location");
                assert(*it++ == "in");
                assert(*it++ == "the");
                assert(*it++ == "container");
                assert(it == vec.end());
                assert(vec.size() == 8);
                assert(vec.capacity() == 8);
        }
        {
                typedef test::throwing_class<test::tracking_class> clazz;
                const std::size_t count = test::tracking_class::instances();
                {
                        ft::vector<clazz> vec(10);
                        vec.reserve(11);
                        clazz::throw_after(2);
                        ASSERT_THROW(vec.insert(vec.begin() + 5, clazz()),
                                     test::too_many_instantiations);
                }
                assert(test::tracking_class::instances() == count);
                clazz::reset();
        }
        {
                typedef test::throwing_class<test::tracking_class> clazz;
                const std::size_t count = test::tracking_class::instances();
                {
                        ft::vector<clazz> vec(10);
                        vec.reserve(11);
                        clazz::throw_after(5);
                        ASSERT_THROW(vec.insert(vec.begin() + 5, clazz()),
                                     test::too_many_instantiations);
                }
                assert(test::tracking_class::instances() == count);
                clazz::reset();
        }
        return 0;
}
