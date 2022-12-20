// vector push_back tests

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

#include <iostream>

int main() {
        {
                ft::vector<int> vec;
                assert(vec.size() == 0);
                vec.push_back(42);
                assert(vec.size() == 1);
                assert(vec.capacity() >= 1);
                assert(vec[0] == 42);
                vec.push_back(5423);
                assert(vec.size() == 2);
                assert(vec.capacity() >= 2);
                assert(vec[1] == 5423);
        }
        {
                test::throwing_class<int> clazz;
                ft::vector<test::throwing_class<int> > vec;
                assert(vec.size() == 0);
                test::throwing_class<int>::make_next_throw();
                try {
                        vec.push_back(clazz);
                        assert(false);
                } catch (const test::too_many_instantiations &ex) {
                        assert(vec.size() == 0);
                }
                test::throwing_class<int>::reset();
        }
        {
                ft::vector<test::throwing_class<int> > vec;
                assert(vec.size() == 0);
                vec.push_back(test::throwing_class<int>(42));
                assert(vec.size() == 1);
                test::throwing_class<int>::make_next_throw();
                try {

                        vec.push_back(test::throwing_class<int>(21));
                        assert(false);
                } catch (const test::too_many_instantiations &ex) {
                        assert(vec[0] == 42);
                }
                test::throwing_class<int>::reset();
                vec.push_back(test::throwing_class<int>(54321));
                assert(vec.size() == 2);
                assert(vec[1] == 54321);
                test::throwing_class<int>::reset();
        }
        return 0;
}
