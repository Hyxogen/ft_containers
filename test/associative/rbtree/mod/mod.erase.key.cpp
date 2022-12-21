#ifndef FT_TEST_STD
#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <allocators.hpp>
#include <cassert>
#include <classes.hpp>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <memory>
#include <set>
#include <vector>

template <typename T, typename U>
void erase_and_validate(T &t, const U &u, bool exists) {
    assert(t.erase(u) == exists);
    t.assert_correct();
}

int main() {
    typedef ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                               std::less<int>,
                               std::allocator<ft::detail::rbnode<int> > >
        rbtree;
    {
        rbtree tree;

        erase_and_validate(tree, 0, false);
        tree.insert(1);
        erase_and_validate(tree, 1, true);
        erase_and_validate(tree, 0, false);
    }
    {
        rbtree tree;

        tree.insert(1);
        tree.insert(0);
        tree.insert(2);

        erase_and_validate(tree, 2, true);
        erase_and_validate(tree, 2, false);
        erase_and_validate(tree, 1, true);
        erase_and_validate(tree, 0, true);
        tree.insert(1);
        erase_and_validate(tree, 0, false);
        erase_and_validate(tree, 1, true);
    }
    {
        rbtree tree;

        tree.insert(1);
        tree.insert(0);
        tree.insert(2);

        erase_and_validate(tree, 0, true);
        erase_and_validate(tree, 1, true);
        erase_and_validate(tree, 2, true);
        tree.insert(1);
        erase_and_validate(tree, 1, true);
    }
    {
        rbtree tree;
        std::set<int> set;
        std::vector<int> numbers;
        std::srand(static_cast<unsigned int>(std::time(NULL)));

        for (int i = 0; i < 800; ++i) {
            int val = std::rand();
            const std::pair<std::set<int>::iterator, bool> set_res =
                set.insert(val);
            const ft::pair<rbtree::iterator, bool> tree_res = tree.insert(val);
            assert(tree_res.second == set_res.second);
            if (!tree_res.second) {
                numbers.push_back(val);
            }
        }

        assert(std::equal(set.begin(), set.end(), tree.begin()));
        for (int i = 0; i < 8000; ++i) {
            const int ins = std::rand() & 1;
            int val = std::rand();

            if (ins || numbers.empty()) {
                const std::pair<std::set<int>::iterator, bool> set_res =
                    set.insert(val);
                const ft::pair<rbtree::iterator, bool> tree_res =
                    tree.insert(val);
                assert(tree_res.second == set_res.second);
                if (!tree_res.second) {
                    numbers.push_back(val);
                }
            } else {
                unsigned int offset =
                    static_cast<unsigned int>(std::abs(val)) % numbers.size();
                val = numbers[offset];

                numbers.erase(numbers.begin() + offset);
                set.erase(val);
                erase_and_validate(tree, val, true);
            }
            assert(std::equal(set.begin(), set.end(), tree.begin()));
        }
    }
    {
        typedef test::tracking_class clazz;
        ft::detail::rbtree<clazz, clazz, ft::detail::use_self<clazz>,
                           std::less<clazz>,
                           std::allocator<ft::detail::rbnode<clazz> > >
            tree;

        for (int i = 0; i < 500; ++i) {
            tree.insert(clazz(i));
        }

        const std::size_t count = clazz::instances();
        for (unsigned int i = 0; i < 500; ++i) {
            erase_and_validate(tree, static_cast<int>(i), true);
            assert(clazz::instances() == count - (i + 1));
        }
    }
    {
        typedef test::allocator_tracker<ft::detail::rbnode<int> > allocator;
        ft::detail::rbtree<int, int, ft::detail::use_self<int>, std::less<int>,
                           allocator>
            tree;

        for (int i = 0; i < 500; ++i) {
            tree.insert(i);
        }

        const std::size_t count = allocator::active();
        for (unsigned int i = 0; i < 500; ++i) {
            erase_and_validate(tree, static_cast<int>(i), true);
            assert(allocator::active() == count - (i + 1));
        }
    }
    {
        typedef test::throwing_class<int> clazz;

        ft::detail::rbtree<clazz, clazz, ft::detail::use_self<clazz>,
                           std::less<clazz>,
                           std::allocator<ft::detail::rbnode<clazz> > >
            tree;

        for (int i = 0; i < 500; ++i) {
            tree.insert(clazz(i));
        }

        for (int i = 0; i < 500; ++i) {
            clazz::throw_after(1);
            erase_and_validate(tree, clazz(i), true);
            clazz::reset();
        }
    }
}
#else
int main() { return 0; }
#endif
