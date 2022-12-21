#include <__tree/red_black_tree.hpp>
#include <cassert>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        assert(tree.empty());
        tree.erase(0);
        assert(tree.empty());
        tree.insert(0);
        assert(!tree.empty());
        tree.erase(0);
        assert(tree.empty());

        for (int i = 0; i < 500; ++i) {
            tree.insert(i);
            assert(!tree.empty());
        }

        for (int i = 0; i < 500; ++i) {
            assert(!tree.empty());
            tree.erase(i);
        }
        assert(tree.empty());
    }
}
