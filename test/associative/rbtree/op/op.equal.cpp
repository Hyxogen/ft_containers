#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>

int main() {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
	{
		rbtree tree1, tree2;

		assert(tree1 == tree2);
	}
	{
		rbtree tree1, tree2;

		tree1.insert(0);
		tree2.insert(0);

		assert(tree1 == tree2);
	}
	{
		rbtree tree1, tree2;

		tree1.insert(1);
		tree1.insert(2);
		tree2.insert(2);
		tree2.insert(1);

		assert(tree1 == tree2);
	}
	{
		rbtree tree1, tree2;

		tree1.insert(1);
		tree1.insert(2);
		tree1.insert(0);
		tree2.insert(2);
		tree2.insert(1);

		assert(!(tree1 == tree2));

	}
}
