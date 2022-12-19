#include <__tree/red_black_tree_new.hpp>
#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <iterators.hpp>

int main() {
        {
                typedef test::range_iterator<int> iterator;
                typedef ft::detail::rbtree<
                    int, int, ft::detail::use_self<int>, std::less<int>,
                    std::allocator<ft::detail::rbnode<int> > >
                    rbtree;

                rbtree tree(test::input_iterator<iterator>(0),
                            test::input_iterator<iterator>(1000));

                rbtree::iterator it = tree.begin();
                for (int i = 0; it != tree.end(); ++it, ++i) {
                        assert(*it == i);
                }
        }
        {
                typedef test::throwing_class<test::tracking_class> clazz;
                typedef test::range_iterator<clazz> iterator;
                typedef ft::detail::rbtree<
                    clazz, clazz, ft::detail::use_self<clazz>,
                    std::less<clazz>,
                    std::allocator<ft::detail::rbnode<clazz> > >
                    rbtree;

                clazz::throw_after(600);
                const std::size_t count = test::tracking_class::instances();

                ASSERT_THROW(
                    rbtree tree(test::input_iterator<iterator>(clazz(0)),
                                test::input_iterator<iterator>(clazz(1000))),
                    test::too_many_instantiations);
                assert(test::tracking_class::instances() == count);
        }
        {
                typedef test::limited_allocator<ft::detail::rbnode<int> >
                    allocator;
                typedef test::range_iterator<int> iterator;
                typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                           std::less<int>, allocator>
                    rbtree;

                const std::size_t count = allocator::active();
                allocator::set_limit(count + 600);

                ASSERT_THROW(rbtree tree(iterator(0), iterator(1000)),
                             std::bad_alloc);
                assert(allocator::active() == count);
        }
}
