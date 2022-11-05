// tests for vector(InputIt first, InputIt last, Allocator alloc)

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
#include <iterator>
#include <iterators.hpp>
#include <sstream>
#include <string>
#include <vector.hpp>
#include <vector>
#include <new>

int main() {
        std::vector<int> stdvec(test::range_iterator<int>(0),
                                test::range_iterator<int>(500));
        {
                ft::vector<int> ftvec(stdvec.begin(), stdvec.end());
                ft::vector<int>::iterator ftit = ftvec.begin();
                for (std::vector<int>::iterator stdit = stdvec.begin();
                     stdit != stdvec.end(); ++stdit, ++ftit) {
                        assert(*stdit == *ftit);
                }
        }
        {
                std::size_t alloc_count
                    = test::allocator_tracker<int>::alloc_count();
                ft::vector<int, test::allocator_tracker<int> > ftvec(
                    stdvec.begin(), stdvec.end());
                assert(test::allocator_tracker<int>::alloc_count()
                           - alloc_count
                       == 1);
        }
        {
                std::stringstream stream("Well hello there :)");
                std::istream_iterator<std::string> str_it(stream);
                ft::vector<std::string> vec(
                    str_it, std::istream_iterator<std::string>());
                ft::vector<std::string>::iterator it = vec.begin();
                assert(*it++ == std::string("Well"));
                assert(*it++ == std::string("hello"));
                assert(*it++ == std::string("there"));
                assert(*it++ == std::string(":)"));
                assert(it == vec.end());
        }
        {
                typedef test::throwing_class<test::tracking_class> clazz;
                typedef test::allocator_tracker<clazz> allocator;
                typedef test::input_iterator<std::vector<clazz>::iterator>
                    input_iterator;
                std::vector<clazz> input(300);

                clazz::throw_after(150);
                const std::size_t instances
                    = test::tracking_class::instances();
                const std::size_t usage = allocator::active();

                try {
                        ft::vector<clazz, allocator> vec(
                            input_iterator(input.begin()),
                            input_iterator(input.end()));
                        assert(0);
                } catch (const test::too_many_instantiations &ex) {
                } catch (...) {
                        assert(0);
                }

                assert(test::tracking_class::instances() == instances);
                assert(allocator::active() == usage);
                clazz::reset();
        }
        {
                typedef test::limited_allocator<int> allocator;
                typedef test::input_iterator<std::vector<int>::iterator>
                    input_iterator;

                allocator::set_limit(160);
                const std::size_t usage = allocator::active();

                try {
                        ft::vector<int, allocator>(
                            input_iterator(stdvec.begin()),
                            input_iterator(stdvec.end()));
                        assert(0);
                } catch (const std::bad_alloc &ex) {
                } catch (...) {
                        assert(0);
                }

                assert(allocator::active() == usage);
                allocator::reset_limit();
        }
        return 0;
}
