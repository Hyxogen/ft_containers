#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <algorithm>
#include <functional>
#include <memory>
#include <iterators.hpp>

int main() {
        {
                typedef test::range_iterator<int> iterator;
                typedef ft::detail::rbtree<
                    int, int, std::less<int>,
                    std::allocator<ft::detail::rbnode<int> > >
                    rbtree;

                const rbtree tree1(iterator(0), iterator(1000));
                const rbtree tree2(tree1);

                assert(std::equal(tree1.begin(), tree1.end(), tree2.begin()));
        }
}
