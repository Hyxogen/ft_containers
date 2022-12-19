#include <benchmark.hpp>
#include <cstdlib>
#include <vector>

int main() {
	set<int> s;
	std::vector<int> v;

	for (int i = 0; i < 10000; ++i) {
		const int x = rand() % 5000;
		v.push_back(x);
		s.insert(x);
	}
        TIME(for (std::vector<int>::iterator it = v.begin(); it != v.end();
                  ++it) { DO_NOT_OPTIMIZE(s.find(*it)); });
}
