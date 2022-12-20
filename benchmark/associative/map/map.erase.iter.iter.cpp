#include <benchmark.hpp>
#include <cstdlib>

int main() {
	typedef int V;
	typedef map<V, int> C;
	C c;

	for (V i = 0; i < 10000; ++i) {
		const V x = rand() % 5000;
		c[x] = rand();
	}

	C::iterator last = c.begin();
	for (C::size_type i = 0; i < c.size() / 3; ++i) {
		++last;
	}
	TIME(c.erase(c.begin(), last));
}
