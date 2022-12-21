#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <compare.hpp>
#include <functional>
#include <memory>

int main() {
    {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   test::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;

        rbtree tree((test::less<int>(3)));

        assert(tree.empty());
        assert(tree.key_comp() == test::less<int>(3));
    }
    {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;

        rbtree tree((std::less<int>()),
                    (std::allocator<ft::detail::rbnode<int> >()));

        assert(tree.empty());
    }
}
