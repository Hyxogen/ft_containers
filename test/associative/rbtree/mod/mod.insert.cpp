#include <__tree/red_black_tree_new.hpp>
#include <cassert>
#include <memory>
#include <classes.hpp>
#include <allocators.hpp>

template <typename Container, typename T>
void assert_unique_insert(Container &container, const T &t) {
        assert(container.insert(t));
        container.assert_correct();
}

template <typename Container, typename T>
void assert_dup_insert(Container &container, const T &t) {
        assert(!container.insert(t));
        container.assert_correct();
}

int main() {
        {
                using namespace ft::detail;
                rbtree<int, int, use_self<int>, std::less<int>,
                       std::allocator<rbnode<int> > >
                    tree;

                assert_unique_insert(tree, 1);
                assert_unique_insert(tree, 2);
                assert_unique_insert(tree, -2);
                assert_unique_insert(tree, 3);
                assert_unique_insert(tree, 4);
                assert_unique_insert(tree, 5);
                assert_unique_insert(tree, 0);
                assert_unique_insert(tree, -1);
        }
        {
                using namespace ft::detail;
                rbtree<int, int, use_self<int>, std::less<int>,
                       std::allocator<rbnode<int> > >
                    tree;

                assert_unique_insert(tree, 0);
                assert_dup_insert(tree, 0);
                assert_dup_insert(tree, 0);
                assert_unique_insert(tree, 1);
                assert_dup_insert(tree, 1);
        }
	{

                using namespace ft::detail;
                rbtree<int, int, use_self<int>, std::less<int>,
                       std::allocator<rbnode<int> > >
                    tree;

		for (int i = 0; i < 500; ++i) {
			assert_unique_insert(tree, i);
			assert_dup_insert(tree, i);
		}
		for (int i = 0; i < 500; ++i) {
			assert_dup_insert(tree, i);
		}
	}
	{
		typedef test::tracking_class clazz;
		const std::size_t count = clazz::instances();
		{
			using namespace ft::detail;
                        rbtree<clazz, clazz, use_self<clazz>, std::less<clazz>,
                               std::allocator<rbnode<clazz> > >
                            tree;

			for (int i = 0; i < 500; i++) {
				assert_unique_insert(tree, clazz(i));
			}
		}
		assert(clazz::instances() == count);
	}
                        // TODO test exception safety
}
