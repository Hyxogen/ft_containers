#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <functional>
#include <classes.hpp>

template <typename T, typename U>
void assert_find(const T &t, const U &u) {
        const typename T::node_type *node = t.search(u);
        assert(node != t.sentinel());
        assert(node->value == u);
}

template <typename T, typename U, typename C>
void assert_find_comp(const T &t, const U &u, const C &c) {
        const typename T::node_type *node = t.search(u);
        assert(node != t.sentinel());
        assert(!c(node->value, u) && !c(u, node->value));
}

template <typename T, typename U>
void assert_no_find(const T &t, const U &u) {
        const typename T::node_type *node = t.search(u);
        assert(node == t.sentinel());
}

int main() {
        typedef ft::detail::rbtree<int, int, std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                assert_no_find(tree, 0);
                assert_no_find(tree, 1);
                assert_no_find(tree, 2);
                assert_no_find(tree, -1);
        }
        {
                rbtree tree;

                tree.insert(0);
                tree.insert(1);
                tree.insert(2);

                assert_find(tree, 0);
                assert_find(tree, 1);
                assert_find(tree, 2);

                assert_no_find(tree, -1);
                tree.insert(-1);
                assert_find(tree, -1);
        }
        {
                typedef test::compare_class<int> clazz;
                ft::detail::rbtree<clazz, clazz, std::less<clazz>,
                                   std::allocator<ft::detail::rbnode<clazz> > >
                    tree;

                tree.insert(0);
                tree.insert(3);
                tree.insert(-3);
                tree.insert(2);
                tree.insert(-2);
                tree.insert(-1);
                tree.insert(1);
                
                for (int i = -3; i <= 3; ++i) {
                        assert_find_comp(tree, i, std::less<clazz>());
                }
        }       
}
