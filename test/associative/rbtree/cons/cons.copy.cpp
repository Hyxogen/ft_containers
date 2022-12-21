#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <cassert>
#include <functional>
#include <iterators.hpp>
#include <memory>

int main() {
    {
        typedef test::range_iterator<int> iterator;
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;

        const rbtree tree1(iterator(0), iterator(1000));
        const rbtree tree2(tree1);

        assert(std::equal(tree1.begin(), tree1.end(), tree2.begin()));
    }
}
#else
int main() {
    return 0;
}
#endif
