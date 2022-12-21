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

        const ft::pair<rbtree::iterator, rbtree::iterator> range =
            tree.equal_range(42);
        assert(range.first == tree.end());
        assert(range.second == tree.end());
    }
    {
        const rbtree tree;

        const ft::pair<rbtree::const_iterator, rbtree::const_iterator> range =
            tree.equal_range(42);
        assert(range.first == tree.end());
        assert(range.second == tree.end());
    }
}
#else
int main() {
    return 0;
}
#endif
