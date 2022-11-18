#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

int main() {
        {
                typedef ft::detail::rbtree<
                    int, int, std::allocator<ft::detail::rbnode<int> > >
                    rbtree;

                rbtree tree;

                tree.insert(1);
                tree.insert(0);
                tree.insert(2);
                assert(tree.is_valid());

                tree.rotate_left(tree.root());
                assert(tree.is_bst());

                tree.rotate_right(tree.root());
                assert(tree.is_valid());

                rbtree ctree;

                ctree.insert(1);
                ctree.insert(0);
                ctree.insert(2);

                rbtree::assert_equal(tree, ctree);
        }
}
