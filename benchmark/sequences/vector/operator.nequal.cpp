#include <algorithm>
#include <benchmark.hpp>
#include <cstdlib>

int main() {
        BENCHMARK(vector<int> vec1(1000);
                  std::generate(vec1.begin(), vec1.end(), rand);
                  vector<int> vec2(vec1); std::generate(
                      vec2.begin() + rand() % 1000, vec2.end(), rand);
                  DO_NOT_OPTIMIZE(vec1 != vec2));
        return 0;
}
