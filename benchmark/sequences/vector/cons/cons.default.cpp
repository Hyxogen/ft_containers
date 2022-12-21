#include <benchmark.hpp>

int main() {
    BENCHMARK(DO_NOT_OPTIMIZE(vector<int>()));
    return 0;
}
