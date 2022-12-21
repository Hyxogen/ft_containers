#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <allocators.hpp>
#include <assert.hpp>
#include <cassert>
#include <classes.hpp>
#include <memory>

template <typename Container, typename T>
void insert_unique_and_validate(Container &container, const T &t) {
    const ft::pair<typename Container::iterator, bool> res =
        container.insert(t);
    assert(res.second);
    assert(*res.first == t);
    container.assert_correct();
}

template <typename Container, typename T>
void insert_duplicate_and_validate(Container &container, const T &t) {
    const ft::pair<typename Container::iterator, bool> res =
        container.insert(t);
    assert(!res.second);
    container.assert_correct();
}

int main() {
    {
        using namespace ft::detail;
        rbtree<int, int, use_self<int>, std::less<int>,
               std::allocator<rbnode<int> > >
            tree;

        insert_unique_and_validate(tree, 1);
        insert_unique_and_validate(tree, 2);
        insert_unique_and_validate(tree, -2);
        insert_unique_and_validate(tree, 3);
        insert_unique_and_validate(tree, 4);
        insert_unique_and_validate(tree, 5);
        insert_unique_and_validate(tree, 0);
        insert_unique_and_validate(tree, -1);
    }
    {
        using namespace ft::detail;
        rbtree<int, int, use_self<int>, std::less<int>,
               std::allocator<rbnode<int> > >
            tree;

        insert_unique_and_validate(tree, 0);
        insert_duplicate_and_validate(tree, 0);
        insert_duplicate_and_validate(tree, 0);
        insert_unique_and_validate(tree, 1);
        insert_duplicate_and_validate(tree, 1);
    }
    {

        using namespace ft::detail;
        rbtree<int, int, use_self<int>, std::less<int>,
               std::allocator<rbnode<int> > >
            tree;

        for (int i = 0; i < 500; ++i) {
            insert_unique_and_validate(tree, i);
            insert_duplicate_and_validate(tree, i);
        }
        for (int i = 0; i < 500; ++i) {
            insert_duplicate_and_validate(tree, i);
        }
    }
    {
        typedef test::tracking_class clazz;
        const std::size_t count = clazz::instances();
        {
            using namespace ft::detail;
            rbtree<clazz, clazz, use_self<clazz>, std::less<clazz>,
                   std::allocator<rbnode<clazz> > >
                tree;

            for (int i = 0; i < 500; i++) {
                insert_unique_and_validate(tree, clazz(i));
            }
        }
        assert(clazz::instances() == count);
    }
    {
        typedef test::throwing_class<test::tracking_class> clazz;
        using namespace ft::detail;

        rbtree<clazz, clazz, use_self<clazz>, std::less<clazz>,
               std::allocator<rbnode<clazz> > >
            tree;

        for (int i = 0; i < 250; ++i) {
            insert_unique_and_validate(tree, clazz(test::tracking_class(i)));
        }
        clazz::throw_after(2);
        const std::size_t count = test::tracking_class::instances();
        ASSERT_THROW(
            insert_unique_and_validate(tree, clazz(test::tracking_class(-1))),
            test::too_many_instantiations);
        assert(test::tracking_class::instances() == count);
        clazz::reset();
        insert_unique_and_validate(tree, clazz(test::tracking_class(-1)));
    }
    {
        using namespace ft::detail;
        typedef test::allocator_tracker<rbnode<int> > allocator;

        const std::size_t active = allocator::active();
        {
            rbtree<int, int, use_self<int>, std::less<int>, allocator> tree;

            for (int i = 0; i < 500; i++) {
                insert_unique_and_validate(tree, i);
            }
        }
        assert(allocator::active() == active);
    }
    {
        using namespace ft::detail;
        typedef test::limited_allocator<rbnode<int> > allocator;

        rbtree<int, int, use_self<int>, std::less<int>, allocator> tree;
        for (int i = 0; i < 250; i++) {
            insert_unique_and_validate(tree, i);
        }

        const std::size_t active = allocator::active();
        allocator::set_limit(active);
        ASSERT_THROW(insert_unique_and_validate(tree, -1), std::bad_alloc);
        assert(allocator::active() == active);
        allocator::reset_limit();
        insert_unique_and_validate(tree, -1);
    }
    // TODO test exception safety
}
#else
int main() {
    return 0;
}
#endif
