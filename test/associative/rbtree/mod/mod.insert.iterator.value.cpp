#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <cassert>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        rbtree::iterator it = tree.begin();
        for (int i = 0; i < 500; ++i) {
            it = tree.insert(it, i);
        }

        int i = 0;
        for (rbtree::iterator cur = tree.begin(); cur != tree.end();
             ++cur, ++i) {
            assert(*cur == i);
        }
        assert(i == 500);
    }
}
#else
int main() {
    return 0;
}
#endif
