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
        rbtree tree1, tree2;

        tree1 = tree2;
        assert(tree1 == tree2);
    }
    {
        rbtree tree1, tree2;

        tree1.insert(6);
        tree1 = tree2;
        assert(tree1 == tree2);
    }
    {
        rbtree tree1, tree2;

        for (int i = 0; i < 500; ++i) {
            tree1.insert(i);
            tree2.insert(500 + i);
        }

        assert(tree1 != tree2);
        tree1 = tree2;
        assert(tree1 == tree2);
        tree1 = tree2;
        assert(tree1 == tree2);
    }
}
