#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <set>

int main() {
        typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                tree.insert(1);
                tree.erase(tree.begin(), tree.end());
                assert(tree.empty());
        }
        {
                rbtree tree;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(i);
                }

                tree.erase(tree.begin(), tree.end());
                assert(tree.empty());
        }
        {
                rbtree tree;
                std::set<int> set;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(i);
                        set.insert(i);
                }

                set.erase(set.find(42), set.find(243));
                tree.erase(tree.find(42), tree.find(243));
                assert(std::equal(tree.begin(), tree.end(), set.begin()));
                assert(std::equal(set.begin(), set.end(), tree.begin()));
        }
}
