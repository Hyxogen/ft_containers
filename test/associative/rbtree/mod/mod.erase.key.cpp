#include <__tree/red_black_tree_new.hpp>
#include <algorithm>
#include <allocators.hpp>
#include <cassert>
#include <classes.hpp>
#include <cstdlib>
#include <functional>
#include <memory>
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
                std::vector<int> numbers;

                for (int i = 0; i < 800; ++i) {
                        int val = rand();
                        while (std::find(numbers.begin(), numbers.end(), val)
                               != numbers.end()) {
                                val = rand();
                        }
                        numbers.push_back(val);
                        tree.insert(val);
                }

                for (int i = 0; i < 8000; ++i) {
                        int del_or_ins = rand();
                        int val = rand();

                        if (del_or_ins & 1 || numbers.empty()) {
                                while (std::find(numbers.begin(),
                                                 numbers.end(), val)
                                       != numbers.end()) {
                                        val = rand();
                                }
                                numbers.push_back(val);
                                tree.insert(val);
                        } else {
                                unsigned int offset
                                    = static_cast<unsigned int>(std::abs(val))
                                      % numbers.size();
                                val = numbers[offset];

                                numbers.erase(numbers.begin() + offset);
                                erase_and_validate(tree, val, true);
                        }
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
                typedef test::allocator_tracker<ft::detail::rbnode<int> >
                    allocator;
                ft::detail::rbtree<int, int, ft::detail::use_self<int>,
                                   std::less<int>, allocator>
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
