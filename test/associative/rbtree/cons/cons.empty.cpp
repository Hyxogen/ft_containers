#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>

int main() {
    {
        using namespace ft::detail;
        rbtree<int, int, use_self<int>, std::less<int>,
               std::allocator<rbnode<int> > >
            tree;
    }
}
#else
int main() { return 0; }
#endif
