#include <map.hpp>
#include <functional>
#include <memory>

int main() {
        {
                ft::map<int, int> mp((std::less<int>()),
                                     std::allocator<int>());

                mp.insert(ft::map<int, int>::value_type(4, 3));
        }
}
