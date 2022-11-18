#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>

int main() {
        using namespace ft::detail;
        {
                rbtree<int, int, std::allocator<rbnode<int> > > tree;
                tree.insert(0);
                assert(tree.is_valid());
                tree.insert(1);
                assert(tree.is_valid());
                tree.insert(2);
                assert(tree.is_valid());
                tree.insert(3);
                assert(tree.is_valid());
                tree.insert(4);
                assert(tree.is_valid());
        }
}
