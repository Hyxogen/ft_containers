#include <set.hpp>
#include <iterators.hpp>
#include <algorithm>
#include <cstdlib>

int main() {
        {
                ft::set<int> set1;

                for (int i = 0; i < 1000; ++i) {
                        set1.insert(rand());
                }
                
                const ft::set<int> set2(set1);
                assert(std::equal(set1.begin(), set1.end(), set2.begin()));
        }
}
