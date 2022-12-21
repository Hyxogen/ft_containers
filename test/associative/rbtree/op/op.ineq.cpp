#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree a, b, c;

        a.insert(1);
        a.insert(2);
        a.insert(3);

        b.insert(7);
        b.insert(8);
        b.insert(9);
        b.insert(10);

        c.insert(1);
        c.insert(2);
        c.insert(3);

        assert(a < b);
        assert(a <= b);
        assert(!(a > b));
        assert(!(a >= b));

        assert(!(a < c));
        assert(a <= c);
        assert(!(a > c));
        assert(a >= c);
    }
}
#else
int main() {
    return 0;
}
#endif
