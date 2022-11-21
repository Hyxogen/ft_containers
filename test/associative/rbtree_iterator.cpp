#include <__tree/red_black_tree.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <set>
#include <vector>
#include <ctime>

int main() {
        typedef ft::detail::rbtree<int, int,
                                   std::allocator<ft::detail::rbnode<int> >,
                                   std::less<int> >
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
                assert(*it++ == 0);
                assert(it == tree.end());

                tree.insert(-1);
                it = tree.begin();
                assert(*it++ == -1);
                assert(*it++ == 0);
                assert(it++ == tree.end());

                tree.insert(1);
                it = tree.begin();
                assert(*it++ == -1);
                assert(*it++ == 0);
                assert(*it++ == 1);
                assert(it == tree.end());

                tree.delete_key(1);
                it = tree.begin();
                assert(*it++ == -1);
                assert(*it++ == 0);
                assert(it == tree.end());
        }
        {
                rbtree tree;
                std::vector<int> numbers;
                std::set<int> set;
                const unsigned int seed
                    = static_cast<unsigned int>(std::time(NULL));

                std::srand(seed);

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
                        bool was_delete = false;

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
                                was_delete = true;
                        }
                        if (!std::equal(set.begin(), set.end(),
                                        tree.begin())) {
                                const std::pair<std::set<int>::iterator,
                                                rbtree::iterator> pos = std::
                                    mismatch(set.begin(), set.end(),
                                             tree.begin());                                
                                const rbtree::node_type *node
                                    = tree.search(*pos.first);

                                rbtree::node_type::debug_print(
                                    tree.root(), tree.sentinel(),
                                    pos.second._current);
                                std::cerr << std::endl << std::endl;
                                rbtree::node_type::debug_print(
                                    tree.root(), tree.sentinel(), node);

                                const std::ptrdiff_t good_distance
                                    = std::distance(set.begin(), pos.first);
                                const std::ptrdiff_t bad_distance
                                    = std::distance(tree.begin(), pos.second);

                                std::cerr << "expected: " << *pos.first
                                          << " got: " << *pos.second
                                          << std::endl;
                                std::cerr << "goffset " << good_distance
                                          << " boffset " << bad_distance
                                          << std::endl;
                                if (was_delete)
                                        std::cerr
                                            << "performed delete operation "
                                               "this iteration";
                                else
                                        std::cerr
                                            << "performed insert operation "
                                               "this iteration";
                                std::cerr << std::endl;
                                std::cerr << "seed: " << seed << std::endl;

                                rbtree::iterator tmp = tree.begin();
                                for (int j = 0; j < 8; ++j, ++tmp) {
                                        std::cout << j << " " << *tmp
                                                  << std::endl;
                                }
                                
                                assert(0);
                        }

                        if (!std::equal(set.rbegin(), set.rend(),
                                        tree.rbegin())) {
                                std::cerr << "seed: " << seed << std::endl;
                                assert(0);
                        }
                }
        }
        {
                rbtree tree;

                for (int i = 0; i < 500; ++i) {
                        tree.insert(i);
                }
                
                rbtree::const_iterator it = tree.begin(), end = tree.end();
                for (int i = 0; it != end; ++it, ++i) {
                        assert(*it == i);
                }
        }
        // TODO write tests that make sure the iterators stay correct when
        // removing or inserting to the ends of the tree
        // TODO add tests for postfix decrement operator rbtree_iterator
}
