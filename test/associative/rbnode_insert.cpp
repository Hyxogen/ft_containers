#include <__tree/red_black_tree.hpp>
#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <functional>
#include <memory>

template <typename T, typename U>
void insert_unique_and_validate(T &t, const U &u) {
        const ft::pair<typename T::iterator, bool> res(t.insert(u));
        assert(*res.first == u);
        assert(res.second == true);
        t.self_check();
}

template <typename T, typename U>
void insert_dup_and_validate(T &t, const U &u) {
        const ft::pair<typename T::iterator, bool> res(t.insert(u));
        assert(res.second == false);
        t.self_check();
}

int main() {
        typedef ft::detail::rbtree<int, int,
                                   std::allocator<ft::detail::rbnode<int> >,
                                   std::less<int> >
            irbtree;
        { irbtree tree; }
        {
                irbtree tree;

                insert_unique_and_validate(tree, 1);
                insert_unique_and_validate(tree, 0);
                insert_unique_and_validate(tree, 2);
                insert_dup_and_validate(tree, 2);
        }
        {
                irbtree tree;

                for (int i = 0; i < 100; ++i) {
                        insert_unique_and_validate(tree, i);
                        insert_dup_and_validate(tree, i);
                }
        }
        {
                irbtree tree;

                insert_unique_and_validate(tree, 5);
                insert_unique_and_validate(tree, 1);
                insert_unique_and_validate(tree, 9);
                insert_unique_and_validate(tree, 3);
                insert_unique_and_validate(tree, 4);
                insert_unique_and_validate(tree, 10);
                insert_unique_and_validate(tree, 8);
                insert_dup_and_validate(tree, 3);
        }
        {
                typedef test::tracking_class clazz;
                typedef ft::detail::rbtree<
                    clazz, clazz, std::allocator<ft::detail::rbnode<clazz> >,
                    std::less<clazz> >
                    rbtree;

                const std::size_t count = clazz::instances();

                {
                        rbtree tree;

                        for (int i = 0; i < 500; i++) {
                                insert_unique_and_validate(tree, clazz(i));
                        }
                }
                assert(count == clazz::instances());
        }
        {
                typedef test::throwing_class<test::tracking_class> clazz;
                typedef ft::detail::rbtree<
                    clazz, clazz, std::allocator<ft::detail::rbnode<clazz> >,
                    std::less<clazz> >
                    rbtree;

                rbtree tree;

                for (int i = 0; i < 250; ++i) {
                        insert_unique_and_validate(
                            tree, clazz(test::tracking_class(i)));
                }
                clazz::throw_after(2);
                const std::size_t count = test::tracking_class::instances();
                ASSERT_THROW(insert_unique_and_validate(
                                 tree, clazz(test::tracking_class(-1))),
                             test::too_many_instantiations);
                assert(count == test::tracking_class::instances());
                clazz::reset();
                insert_unique_and_validate(tree, clazz(-1));
        }
        {
                typedef test::allocator_tracker<ft::detail::rbnode<int> >
                    allocator;
                typedef ft::detail::rbtree<int, int, allocator,
                                           std::less<int> >
                    rbtree;

                const std::size_t active = allocator::active();

                {
                        rbtree tree;

                        for (int i = 0; i < 500; ++i) {
                                insert_unique_and_validate(tree, i);
                        }
                }
                assert(active == allocator::active());
        }
}
