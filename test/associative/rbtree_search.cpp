#include <__tree/red_black_tree.hpp>
#include <cassert>

template <typename T, typename U>
void assert_find(const T &t, const U &u) {
        const typename T::node_type *node = t.search(u);
        assert(node != t.sentinel());
        assert(node->value == u);
}

template <typename T, typename U>
void assert_no_find(const T &t, const U &u) {
        const typename T::node_type *node = t.search(u);
        assert(node == t.sentinel());
}

int main() {
        typedef ft::detail::rbtree<int, int,
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
}
