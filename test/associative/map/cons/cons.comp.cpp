#include <test.hpp>
#include <cassert>
#include <compare.hpp>


int main() {
    {
        typedef int V;
        typedef test::less<V> C;
        typedef ft::map<V, bool, C> M;

        M m(C(42));
        assert(m.empty());
        assert(m.key_comp() == C(42));
    }
}
