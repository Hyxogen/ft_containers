#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>
#include <functional>

int main() {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree((std::less<int>()));

                assert(tree.empty());
	}
	{
                rbtree tree((std::less<int>()),
                            (std::allocator<ft::detail::rbnode<int> >()));
		
                assert(tree.empty());
	}
}
