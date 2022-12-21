#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <functional>
#include <memory>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        for (int i = 0; i < 500; i++) {
            tree.insert(i);
        }

        rbtree::iterator it = tree.begin();
        for (int i = 0; it != tree.end(); ++i, ++it) {
            assert(*it == i);
        }
    }
    {
        rbtree tree;

        for (int i = 0; i < 500; i++) {
            tree.insert(i);
        }

        rbtree::iterator it = tree.end();
        int i = 500;
        while (it != tree.begin()) {
            assert(*--it == --i);
        }
    }
}
#else
int main() { return 0; }
#endif
