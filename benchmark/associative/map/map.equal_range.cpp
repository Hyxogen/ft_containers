#include <benchmark.hpp>
#include <cstdlib>

int main() {
    map<int, int> m;

    for (int i = 0; i < 10000; ++i) {
        const int x = rand() % 5000;
        m[x] = rand();
    }
    BENCHMARK_N(
        for (int i = 0; i < 10000; ++i) { DO_NOT_OPTIMIZE(m.equal_range(i)); },
        1000);
}
