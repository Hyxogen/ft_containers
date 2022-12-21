#include <cassert>
#include <test.hpp>

int main() {
    ft::vector<int> vec1;
    ft::vector<int> vec2;
    ft::vector<int> vec3;

    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    vec2.push_back(7);
    vec2.push_back(8);
    vec2.push_back(9);
    vec2.push_back(10);

    vec3.push_back(1);
    vec3.push_back(2);
    vec3.push_back(3);

    assert(!(vec1 == vec2));
    assert(vec1 != vec2);
    assert(vec1 < vec2);
    assert(vec1 <= vec2);
    assert(!(vec1 > vec2));
    assert(!(vec1 >= vec2));

    assert(vec1 == vec3);
    assert(!(vec1 != vec3));
    assert(!(vec1 < vec3));
    assert(vec1 <= vec3);
    assert(!(vec1 > vec3));
    assert(vec1 >= vec3);
    return 0;
}
