#include <__tree/red_black_tree.hpp>
#include <cassert>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        assert(tree.count(0) == 0);
        tree.insert(0);
        assert(tree.count(0) == 1);
        tree.insert(0);
        assert(tree.count(0) == 1);
    }
    {
        rbtree tree;

        for (int i = 0; i < 500; ++i) {
            tree.insert(i);
        }
        for (int i = 0; i < 500; ++i) {
            (void)i;
            assert(tree.count(i) == 1);
            assert(tree.count(i + 500) == 0);
        }
    }
}
