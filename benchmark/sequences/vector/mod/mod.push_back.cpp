#include <benchmark.hpp>
#include <cstdlib>

int main() {
        vector<int> vec;
        BENCHMARK(vec.push_back(rand()));
        DO_NOT_OPTIMIZE(vec);
        return 0;
}
