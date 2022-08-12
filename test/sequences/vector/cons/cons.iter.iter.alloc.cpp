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
#include <iterator>
#include <iterators.hpp>
#include <sstream>
#include <string>
#include <vector.hpp>
#include <vector>

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
        return 0;
}
