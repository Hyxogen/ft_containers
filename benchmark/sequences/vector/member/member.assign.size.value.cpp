#include <benchmark.hpp>

int main() {
    BENCHMARK(vector<int> tmp; tmp.assign(500, 42));
    return 0;
}
