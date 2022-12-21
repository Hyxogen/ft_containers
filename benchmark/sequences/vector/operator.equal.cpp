#include <algorithm>
#include <benchmark.hpp>
#include <cstdlib>

int main() {
    BENCHMARK(vector<int> vec(1000);
              std::generate(vec.begin(), vec.end(), rand);
              DO_NOT_OPTIMIZE(vec == vec));
    return 0;
}
