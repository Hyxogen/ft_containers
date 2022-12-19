#include <__tree/red_black_tree_new.hpp>
#include <cassert>
#include <set>
#include <algorithm>

int main() {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
	{
		rbtree tree1, tree2;

		assert(tree1 == tree2);
		tree1.swap(tree2);
		assert(tree1.empty());
		assert(tree2.empty());
		assert(tree1 == tree2);
	}
	{
		rbtree tree1, tree2;

		tree1.insert(1);
		tree1.swap(tree2);
		assert(tree1.size() == 0);
		assert(tree2.size() == 1);
	}
	{
		rbtree tree1, tree2;

		for (int i = 0; i < 500; ++i) {
			tree1.insert(i);
			tree2.insert(i + 500);
		}

		tree1.swap(tree2);

		for (int i = 0; i < 500; ++i) {
			tree1.insert(i);
			tree2.insert(i + 500);
		}

		assert(std::equal(tree1.begin(), tree1.end(), tree2.begin()));
		assert(std::equal(tree2.begin(), tree2.end(), tree1.begin()));
	}
	{
		rbtree tree1, tree2;
		std::set<int> set1, set2;

		for (int i = 0; i < 101; ++i) {
			tree1.insert(i);
			set1.insert(i);
		}
		for (int i = 101; i < 500; ++i) {
			tree2.insert(i);
			set2.insert(i);
		}

		tree1.swap(tree2);
		set1.swap(set2);

		assert(tree1.size() == set1.size());
		assert(tree2.size() == set2.size());
		assert(std::equal(tree1.begin(), tree1.end(), set1.begin()));
		assert(std::equal(set1.begin(), set1.end(), tree1.begin()));

		assert(std::equal(tree2.begin(), tree2.end(), set2.begin()));
		assert(std::equal(set2.begin(), set2.end(), tree2.begin()));
	}
}
