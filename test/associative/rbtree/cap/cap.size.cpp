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

        assert(tree.size() == 0);
        tree.erase(0);
        assert(tree.size() == 0);
        tree.insert(0);
        assert(tree.size() == 1);
        tree.erase(0);
        assert(tree.size() == 0);

        for (int i = 0; i < 500; ++i) {
            tree.insert(i);
            assert(tree.size() == static_cast<rbtree::size_type>(i + 1));
        }

        for (int i = 0; i < 500; ++i) {
            tree.erase(i);
            assert(tree.size() == static_cast<rbtree::size_type>(500 - i - 1));
        }
    }
}
#else
int main() { return 0; }
#endif
