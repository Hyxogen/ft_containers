#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>

template <typename T>
void erase_and_validate(T &t, const typename T::iterator &it) {
    t.erase(it);
    t.assert_correct();
}

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        for (int i = 0; i < 500; ++i) {
            tree.insert(i);
        }

        rbtree::iterator it = tree.begin();
        for (int i = 0; it != tree.end(); ++i) {
            rbtree::iterator tmp = it++;
            erase_and_validate(tree, tmp);
            assert(tree.find(i) == tree.end());
        }
    }
}
#else
int main() {
    return 0;
}
#endif
