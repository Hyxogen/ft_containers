#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <functional>
#include <memory>

int main() {
    using namespace ft::detail;
    {
        rbtree<int, int, use_self<int>, std::less<int>,
               std::allocator<rbnode<int> > >
            tree;

        assert(tree.key_comp()(0, 1));
        assert(!tree.key_comp()(0, 0));
        assert(!tree.key_comp()(1, 0));
    }
    {

        rbtree<int, int, use_self<int>, std::greater<int>,
               std::allocator<rbnode<int> > >
            tree;

        assert(!tree.key_comp()(0, 1));
        assert(!tree.key_comp()(0, 0));
        assert(tree.key_comp()(1, 0));
    }
}
#else
int main() { return 0; }
#endif
