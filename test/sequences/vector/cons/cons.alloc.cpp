#include <vector.hpp>
#include <allocators.hpp>
#include <cassert>

int main() {
	{
            test::allocator_wrapper<int> alloc;
            std::size_t count = test::calls["copy"];
            ft::vector<int, test::allocator_wrapper<int> > vec(alloc);
            assert(vec.empty());
            assert((test::calls["copy"] - count) == 1);
        }
        {
            typedef int V;
            typedef test::stateful_allocator<int, V> A;
            typedef ft::vector<V, A> M;
            M m(A(11));

            assert(m.get_allocator() == A(11));
        }
	return 0;
}
