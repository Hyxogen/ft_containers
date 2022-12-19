#include <cassert>
#include <set.hpp>

int main() {
        {
                typedef ft::set<int> C;

                C c1, c2;
                assert(c1 == c2);

                c1.insert(0);
                assert(c1 != c2);

                c2.insert(0);
                assert(c1 == c2);

                c1.insert(0);
                assert(c1 == c2);

                c2.insert(1);
                assert(c1 != c2);
        }
}
