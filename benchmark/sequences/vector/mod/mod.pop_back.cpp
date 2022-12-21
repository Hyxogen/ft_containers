#include <benchmark.hpp>

int main() {
    BENCHMARK(vector<int> vec(10000); vec.pop_back(); DO_NOT_OPTIMIZE(vec));
    return 0;
}
