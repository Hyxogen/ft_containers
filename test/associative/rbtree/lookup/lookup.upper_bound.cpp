#include <__tree/red_black_tree_new.hpp>
#include <cassert>

int main() {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                assert(tree.upper_bound(42) == tree.end());
        }
        {
                const rbtree tree;

                assert(tree.upper_bound(42) == tree.end());
        }
        {
                rbtree tree;

                tree.insert(0);

                assert(tree.upper_bound(1) == tree.end());
                assert(tree.upper_bound(0) == tree.end());
                assert(tree.upper_bound(-1) == tree.begin());
        }
        {
                rbtree tree;

                tree.insert(0);
                tree.insert(42);
                tree.insert(9);
                tree.insert(-11);
                tree.insert(34);

                assert(*tree.upper_bound(0) == 9);
                assert(*tree.upper_bound(1) == 9);
                assert(*tree.upper_bound(-10) == 0);
                assert(*tree.upper_bound(-11) == 0);
                assert(*tree.upper_bound(-12) == -11);
                assert(*tree.upper_bound(11) == 34);
                assert(*tree.upper_bound(34) == 42);
                assert(*tree.upper_bound(39) == 42);
                assert(tree.upper_bound(42) == tree.end());
                assert(tree.upper_bound(53) == tree.end());
        }
}
