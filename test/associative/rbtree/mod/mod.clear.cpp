#include <__tree/red_black_tree.hpp>
#include <cassert>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        tree.clear();
        assert(tree.empty());

        tree.insert(0);
        tree.clear();
        assert(tree.empty());

        tree.insert(0);
        tree.clear();
        assert(tree.empty());
    }
    {
        rbtree tree;

        for (int i = 0; i < 500; i++) {
            tree.insert(i);
        }

        tree.clear();
        assert(tree.empty());

        for (int i = 0; i < 500; i++) {
            const ft::pair<rbtree::iterator, bool> res = tree.insert(i);
            assert(*res.first == i);
            assert(res.second);
        }
    }
}
