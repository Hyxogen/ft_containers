#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <functional>
#include <memory>

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        for (int i = 0; i < 500; i++) {
            tree.insert(i);
        }

        rbtree::const_reverse_iterator it = tree.rbegin();
        for (int i = 499; it != const_cast<const rbtree &>(tree).rend();
             --i, ++it) {
            assert(*it == i);
        }
    }
    {
        rbtree tree;

        for (int i = 0; i < 500; i++) {
            tree.insert(i);
        }

        rbtree::const_reverse_iterator it = tree.rend();
        int i = 0;
        while (it != const_cast<const rbtree &>(tree).rbegin()) {
            assert(*--it == i++);
        }
    }
}
