#include <benchmark.hpp>
#include <cstdlib>

int main() {
    typedef stack<int> C;
    C c = C();

    BENCHMARK(c.push(rand()); DO_NOT_OPTIMIZE(c.top()););
}
