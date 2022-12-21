#include <benchmark.hpp>
#include <cstdlib>

int main() {
    set<int> s;

    for (int i = 0; i < 10000; ++i) {
        const int x = rand() % 5000;
        s.insert(x);
    }
    BENCHMARK_N(
        for (int i = 0; i < 10000; ++i) { DO_NOT_OPTIMIZE(s.equal_range(i)); },
        1000);
}
