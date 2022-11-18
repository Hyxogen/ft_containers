#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>

template <typename T, typename U>
void insert_and_validate(T &t, const U &u) {
        t.insert(u);
        assert(t.is_valid());
}

int main() {
        typedef ft::detail::rbtree<int, int,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                for (int i = 0; i < 100; ++i) {
                        insert_and_validate(tree, i);
                }
        }
}
