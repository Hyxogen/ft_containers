#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <cassert>
#include <set>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        std::set<int> set;

        for (int i = 0; i < 500; ++i) {
            set.insert(i);
        }

        rbtree tree;
        tree.insert(set.begin(), set.end());
        assert(std::equal(set.begin(), set.end(), tree.begin()));
        assert(std::equal(tree.begin(), tree.end(), set.begin()));
    }
}
#else
int main() { return 0; }
#endif
