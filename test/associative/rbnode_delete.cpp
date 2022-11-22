#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <vector>
#include <classes.hpp>
#include <allocators.hpp>
#include <functional>

template <typename T, typename U> void delete_and_validate(T &t, const U &u) {
        t.delete_node(u);
        t.self_check();
}

template <typename T, typename U>
void delete_key_and_validate(T &t, const U &u) {
        t.delete_key(u);
        t.self_check();
}

int main() {
        typedef ft::detail::rbtree<int, int, std::less<int>,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                tree.insert(1);
                delete_and_validate(tree, tree.root());
                assert(tree.root() == tree.sentinel());
        }
        {
                rbtree tree;

                tree.insert(1);
                tree.insert(0);
                tree.insert(2);

                delete_and_validate(tree, tree.root()->left);
                delete_and_validate(tree, tree.root()->right);
                delete_and_validate(tree, tree.root());
                assert(tree.root() == tree.sentinel());
                tree.insert(1);
                delete_and_validate(tree, tree.root());
        }
        {
                rbtree tree;

                tree.insert(1);
                tree.insert(0);
                tree.insert(2);

                delete_and_validate(tree, tree.root());
                delete_and_validate(tree, tree.root()->left);
                delete_and_validate(tree, tree.root());
                assert(tree.root() == tree.sentinel());
                tree.insert(1);
                delete_and_validate(tree, tree.root());
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
                                delete_key_and_validate(tree, val);
                        }
                }
        }
        {
                typedef test::tracking_class clazz;
                ft::detail::rbtree<clazz, clazz, std::less<clazz>,
                                   std::allocator<ft::detail::rbnode<clazz> > >
                    tree;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(clazz(i));
                }

                const std::size_t count = clazz::instances();
                for (unsigned int i = 0; i < 500; ++i) {
                        delete_key_and_validate(tree, static_cast<int>(i));
                        assert(clazz::instances() == count - (i + 1));
                }
        }
        {
                typedef test::allocator_tracker<ft::detail::rbnode<int> >
                    allocator;

                ft::detail::rbtree<int, int, std::less<int>, allocator> tree;
                
                for (int i = 0; i < 500; ++i) {
                        tree.insert(i);
                }

                const std::size_t count = allocator::active();
                for (unsigned int i = 0; i < 500; ++i) {
                        delete_key_and_validate(tree, static_cast<int>(i));
                        assert(allocator::active() == count - (i + 1));
                }
        }
        {
                typedef test::throwing_class<int> clazz;

                ft::detail::rbtree<clazz, clazz, std::less<clazz>,
                                   std::allocator<ft::detail::rbnode<clazz> > >
                    tree;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(clazz(i));
                }
                for (int i = 0; i < 500; ++i) {
                        clazz::throw_after(1);
                        delete_key_and_validate(tree, clazz(i));
                        clazz::reset();
                }
        }
}
