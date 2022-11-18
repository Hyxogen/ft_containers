#include <__tree/red_black_tree.hpp>
#include <cassert>

int main() {
        using namespace ft::detail;
        {
                rbtree<int, int> tree;
                rbnode<int> zero(RB_BLACK, 0), one(RB_BLACK, 1),
                    two(RB_BLACK, 2), three(RB_BLACK, 3), four(RB_BLACK, 4);

                tree.insert(&zero);
                assert(tree._root->black_height() != 0);
                tree.insert(&one);
                assert(tree._root->black_height() != 0);
                tree.insert(&two);
                assert(tree._root->black_height() != 0);
                tree.insert(&three);
                assert(tree._root->black_height() != 0);
                tree.insert(&four);
                assert(tree._root->black_height() != 0);
        }
}
