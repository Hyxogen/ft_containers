#include <benchmark.hpp>
#include <cstdlib>

int main() {
    BENCHMARK(vector<int> vec(10000, 42);
              vec.insert(vec.begin() + rand() % 10000, rand() % 100, 42));
    return 0;
}
