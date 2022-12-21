#include <algorithm>
#include <benchmark.hpp>
#include <cstdlib>

int main() {
    vector<int> input(1000);
    std::generate(input.begin(), input.end(), rand);
    BENCHMARK(vector<int> vec(1000, 42); vec.insert(vec.begin() + rand() % 1000,
                                                    input.begin(), input.end());
              DO_NOT_OPTIMIZE(vec));
    return 0;
}
