#include <set.hpp>
#include <functional>
#include <memory>
#include <string>

int main() {
        {
                ft::set<std::string> set((std::less<std::string>()),
                                         std::allocator<std::string>());

                set.insert("hello there");
        }
}
