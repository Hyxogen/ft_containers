#include <allocators.hpp>
#include <cassert>
#include <compare.hpp>
#include <map.hpp>

int main() {
    {
        typedef int V;
        typedef test::stateful_allocator<int, V> A;
        typedef test::less<V> C;
        typedef ft::map<V, bool, C, A> M;

        M m(C(42), A(11));
        assert(m.empty());
        assert(m.key_comp() == C(42));
        assert(m.get_allocator() == A(11));
    }
}
