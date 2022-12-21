#include <algorithm>
#include <benchmark.hpp>
#include <cstdlib>
#include <vector>

int main() {
    typedef int V;
    typedef map<V, int> M;
    typedef std::vector<V> U;
    U u;
    M m;

    for (int i = 0; i < 10000; ++i) {
        const int key = rand() % 5000;
        u.push_back(key);
        m[key] = rand();
    }

    BENCHMARK_N(
        for (U::iterator it = u.begin(); it != u.end();
             ++it) { DO_NOT_OPTIMIZE(m.count(*it)); },
        1000);
}
