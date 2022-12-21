#include <benchmark.hpp>
#include <cstdlib>

int main() {
    vector<int> vec(10000);
    BENCHMARK(vec.resize(rand() % 10000); DO_NOT_OPTIMIZE(vec));
    return 0;
}
