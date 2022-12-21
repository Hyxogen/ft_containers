#include <benchmark.hpp>
#include <iterators.hpp>

int main() {
    BENCHMARK(DO_NOT_OPTIMIZE(vector<int>(test::range_iterator<int>(0),
                                          test::range_iterator<int>(500))));
}
