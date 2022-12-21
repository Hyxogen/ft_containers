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

        assert(tree.lower_bound(42) == tree.end());
    }
    {
        const rbtree tree;

        assert(tree.lower_bound(42) == tree.end());
    }
    {
        rbtree tree;

        tree.insert(0);

        assert(tree.lower_bound(1) == tree.end());
        assert(tree.lower_bound(0) == tree.begin());
        assert(tree.lower_bound(-1) == tree.begin());
    }
    {
        rbtree tree;

        tree.insert(0);
        tree.insert(42);
        tree.insert(9);
        tree.insert(-11);
        tree.insert(34);

        assert(*tree.lower_bound(1) == 9);
        assert(*tree.lower_bound(-10) == 0);
        assert(*tree.lower_bound(11) == 34);
        assert(*tree.lower_bound(34) == 34);
        assert(*tree.lower_bound(39) == 42);
        assert(tree.lower_bound(53) == tree.end());
    }
}
#else
int main() {
    return 0;
}
#endif
