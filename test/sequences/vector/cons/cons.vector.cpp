// simple tests for vector(const vector &other)

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
#include <allocators.hpp>
#include <classes.hpp>

int main() {
        
        {
                ft::vector<int> vec;
                vec.push_back(5);
                vec.push_back(21);
                vec.push_back(42);
                vec.push_back(34123);
                ft::vector<int> cpy(vec);

                ft::vector<int>::iterator vecit = vec.begin(),
                                          cpyit = cpy.begin();
                for (; vecit != vec.end(); ++vecit, ++cpyit) {
                        assert(*vecit == *cpyit);
                        assert(vecit != cpyit);
                }
        }
        {
                //FIXME: int below here should be test::throwing_class<int>
                ft::vector<
                    test::throwing_class<int>,
                    test::allocator_tracker<test::throwing_class<int> > >
                    vec;
                vec.push_back(test::throwing_class<int>(5));
                vec.push_back(test::throwing_class<int>(21));
                vec.push_back(test::throwing_class<int>(42));
                vec.push_back(test::throwing_class<int>(5451341));
                std::size_t used = test::allocator_tracker<
                        test::throwing_class<int> >::active();
                test::throwing_class<int>::make_next_throw();
                try {
                        //FIXME: int below should be test::throwing_class<int>
                        ft::vector<test::throwing_class<int>,
                                   test::allocator_tracker<
                                       test::throwing_class<int> > >
                            cpy(vec);
                        assert(false);
                } catch (const test::too_many_instantiations &ex) {
                        assert(test::allocator_tracker<
                                   test::throwing_class<int> >::active()
                               == used);
                }
                test::throwing_class<int>::reset();
        }
        return 0;
}
