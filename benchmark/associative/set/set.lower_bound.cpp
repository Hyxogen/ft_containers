#include <benchmark.hpp>
#include <cstdlib>

int main() {
	set<int> s;

	for (int i = 0; i < 10000; ++i) {
		const int x = rand() % 5000;
		s.insert(x);
	}
        TIME(for (int i = 0; i < 10000;
                  ++i) { DO_NOT_OPTIMIZE(s.lower_bound(i)); });
}
