#include <benchmark.hpp>
#include <cstdlib>

int main() {
    typedef int V;
    typedef map<V, int> C;
    BENCHMARK_N(
        C c;

        for (V i = 0; i < 10000; ++i) {
            const V x = rand() % 5000;
            c[x] = rand();
        } DO_NOT_OPTIMIZE(c);
        c.clear();, 10);
}
