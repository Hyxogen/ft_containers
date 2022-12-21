#include <benchmark.hpp>
#include <cstdlib>

int main() {
    map<int, int> mp;
    BENCHMARK(DO_NOT_OPTIMIZE(
        mp.insert(map<int, int>::value_type(rand() % 500, rand()))));
    DO_NOT_OPTIMIZE(mp);
    return 0;
}
