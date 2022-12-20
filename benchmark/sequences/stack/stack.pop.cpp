#include <benchmark.hpp>
#include <cstdlib>

int main() {
	typedef int V;
	typedef stack<V> C;
	C c = C();

	for (V i = 0; i <= BENCHMARK_ITER; ++i) {
		c.push(i);
	}

	BENCHMARK(c.pop(); DO_NOT_OPTIMIZE(c.top()););
}
