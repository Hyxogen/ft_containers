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
	return 0;
}
