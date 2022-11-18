#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
        using namespace ft::detail;
        {
                rbnode<int> root(RB_BLACK, 1), left(RB_BLACK, 0),
                        right(RB_BLACK, 2);

                root.left = &left;
                root.right = &right;
                try {
                        assert(root.black_height() == 2);
                } catch (const std::logic_error &ex) {
                        std::cerr << ex.what() << std::endl;
                }

                rbtree<int, int> tree;
                tree._root = &root;

                tree.rotate_left(tree._root);
                assert(tree._root->is_bst());
                
                tree.rotate_right(tree._root);
                assert(tree._root->is_bst());

                  rbnode<int> croot(RB_BLACK, 1), cleft(RB_BLACK, 0),
                        cright(RB_BLACK, 2);
                croot.left = &cleft;
                croot.right = &cright;

                assert(root == croot);
        }
}
