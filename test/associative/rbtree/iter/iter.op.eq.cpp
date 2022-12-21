#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <functional>
#include <memory>

int main() {
    using namespace ft::detail;
    typedef int V;
    typedef rbtree<V, V, use_self<V>, std::less<V>, std::allocator<rbnode<V> > >
        M;
    typedef M::iterator I;
    {
        I it1, it2;

        assert(it1 == it2);
    }
    {
        M m;

        I it1 = m.begin(), it2 = m.begin();

        assert(it1 == it2);
    }
}
#else
int main() {
    return 0;
}
#endif
