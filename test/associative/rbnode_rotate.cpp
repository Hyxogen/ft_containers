#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <memory>

int main() {
        using namespace ft::detail;
        {
                rbtree<int, int, std::allocator<rbnode<int> > > tree;

                tree.insert(1);
                tree.print();
                tree.insert(0);
                tree.print();
                tree.insert(2);
                tree.print();
                assert(tree.is_valid());
                
                tree.rotate_left(tree.root());
                assert(tree.is_bst());
                
                tree.rotate_right(tree.root());
                assert(tree.is_valid());

                rbtree<int, int, std::allocator<rbnode<int> > > ctree;

                tree.insert(1);
                tree.insert(0);
                tree.insert(2);
                
                assert(tree == ctree);
        }
}
