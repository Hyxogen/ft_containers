#include <test.hpp>
#include <algorithm>
#include <allocators.hpp>
#include <cstdlib>
#include <iterators.hpp>
#include <cassert>
#include <string>

int main() {
    {
        typedef int K;
        typedef std::string V;
        typedef ft::pair<K, V> P;
        typedef std::less<K> C;
        typedef test::stateful_allocator<int, P> A;
        typedef ft::map<K, V, C, A> M;

        P p[] = {
            P(1, "Hi"),         P(1, "There"), P(2, "ft"),
            P(2, "containers"), P(2, "thing"), P(2, "stuff"),
        };

        M m1(p, p + sizeof(p) / sizeof(p[0]), C(), A(11));

        const M m2(m1);
        assert(std::equal(m1.begin(), m1.end(), m2.begin()));
        assert(m2.get_allocator() == A(11));
    }
}
