#include <benchmark.hpp>

int main() {
    BENCHMARK(DO_NOT_OPTIMIZE(vector<int>(500)));
    return 0;
}
