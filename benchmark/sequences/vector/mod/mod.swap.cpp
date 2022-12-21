#include <benchmark.hpp>

int main() {
    vector<int> vec1(1000, 42);
    vector<int> vec2(1000, 21);
    BENCHMARK(vec1.swap(vec2); DO_NOT_OPTIMIZE(vec1));
    return 0;
}
