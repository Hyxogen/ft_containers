#include <benchmark.hpp>
#include <algorithm>
#include <cstdlib>

int main() {
	typedef map<int, int> M;
	M m;

	for (int i = 0; i < 10000; ++i) {
		m[i] = rand();
	}

	const M::value_type find_value = make_pair(10000, -1);
	BENCHMARK_N(DO_NOT_OPTIMIZE(std::find(m.begin(), m.end(), find_value)), 1000);
}
