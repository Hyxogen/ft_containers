#include <set.hpp>
#include <cassert>
#include <iterators.hpp>
#include <functional>
#include <memory>

int main() {
        {
                typedef test::input_iterator<test::range_iterator<int> >
                    iterator;
                ft::set<int> set(iterator(0), iterator(1000), std::less<int>(),
                                 std::allocator<int>());

                ft::set<int>::iterator it = set.begin();
                for (int i = 0; it != set.end(); ++it, ++i) {
                        assert(*it == i);
                }
        }
}
