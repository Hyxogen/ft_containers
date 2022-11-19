#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <set>
#include <vector>

int main() {
        typedef ft::detail::rbtree<int, int,
                                   std::allocator<ft::detail::rbnode<int> > >
            rbtree;
        {
                rbtree tree;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(i);
                }

                rbtree::iterator begin = tree.begin();
                rbtree::iterator end = tree.end();
                for (int i = 0; begin != end; ++begin, ++i) {
                        assert(*begin == i);
                }

                begin = tree.begin();
                for (int i = 0; i < 500; ++i) {
                        assert(*--end == (500 - i - 1));
                }

                rbtree::reverse_iterator rbegin = tree.rbegin();
                for (int i = 1; rbegin != tree.rend(); ++rbegin, ++i) {
                        assert(*rbegin == (500 - i));
                }

                tree.delete_key(342);
                begin = tree.begin();
                for (int i = 0; begin != tree.end(); ++begin, ++i) {
                        if (i != 342)
                                assert(*begin == i);
                        else
                                ++i;
                }
        }
        {
                rbtree tree;

                assert(tree.begin() == tree.end());

                tree.insert(0);
                assert(tree.begin() != tree.end());
                tree.delete_key(0);
                assert(tree.begin() == tree.end());

                tree.insert(0);

                rbtree::iterator it = tree.begin();
                assert(*it == 0);
                assert(++it == tree.end());

                tree.insert(-1);
                it = tree.begin();
                assert(*it == -1);
                assert(*++it == 0);
                assert(++it == tree.end());

                tree.insert(1);
                it = tree.begin();
                assert(*it == -1);
                assert(*++it == 0);
                assert(*++it == 1);
                assert(++it == tree.end());

                tree.delete_key(1);
                it = tree.begin();
                assert(*it == -1);
                assert(*++it == 0);
                assert(++it == tree.end());
        }
        {
                // TODO check why this test case fails
                rbtree tree;
                std::vector<int> numbers;
                std::set<int> set;

                for (int i = 0; i < 800; ++i) {
                        int val = rand();
                        while (std::find(numbers.begin(), numbers.end(), val)
                               != numbers.end()) {
                                val = rand();
                        }
                        numbers.push_back(val);
                        tree.insert(val);
                        set.insert(val);
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
                                set.insert(val);
                        } else {
                                unsigned int offset
                                    = static_cast<unsigned int>(std::abs(val))
                                      % numbers.size();
                                val = numbers[offset];

                                numbers.erase(numbers.begin() + offset);
                                tree.delete_key(val);
                                set.erase(val);
                        }
                        assert(
                            std::equal(set.begin(), set.end(), tree.begin()));
                }
        }
        // TODO write tests that make sure the iterators stay correct when
        // removing or inserting to the ends of the tree
}
