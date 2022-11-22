#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <functional>
#include <memory>

int main() {
        typedef ft::detail::rbtree<int, int, std::greater<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(i);
                }

                rbtree::iterator forward_it = tree.begin();
                rbtree::reverse_iterator reverse_it = tree.rbegin();

                for (int i = 0;
                     forward_it != tree.end() && reverse_it != tree.rend();
                     ++forward_it, ++reverse_it, ++i) {
                        assert(*forward_it == 500 - 1 - i);
                        assert(*reverse_it == i);
                }
        }
}
