#include <__tree/red_black_tree.hpp>
#include <cassert>
#include <memory>
#include <vector>
#include <cstdlib>
#include <algorithm>

template <typename T, typename U> void delete_and_validate(T &t, const U &u) {
        t.delete_node(u);
        assert(t.is_valid());
}

template <typename T, typename U>
void delete_key_and_validate(T &t, const U &u) {
        t.delete_key(u);
        if (!t.is_valid()) {
                t.print();
                t.self_check();
        }
}

int main() {
        typedef ft::detail::rbtree<int, int,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                tree.insert(1);
                delete_and_validate(tree, tree.root());
                assert(tree.root() == tree.sentinel());
                std::cout << std::endl;
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

                for (int i = 0; i < 500; ++i) {
                        int val = rand();
                        while (std::find(numbers.begin(), numbers.end(), val)
                               != numbers.end()) {
                                val = rand();
                        }
                        numbers.push_back(val);
                        tree.insert(val);
                }
                
                for (int i = 0; i < 5000; ++i) {
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
}
