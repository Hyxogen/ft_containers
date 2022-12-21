#include <benchmark.hpp>
#include <iterators.hpp>

int main() {
    const vector<int> tmp(test::range_iterator<int>(0),
                          test::range_iterator<int>(500));
    BENCHMARK(DO_NOT_OPTIMIZE(vector<int>(tmp)));
}
