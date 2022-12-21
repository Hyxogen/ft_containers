#include <cassert>
#include <set>
#include <string>
#include <utility.hpp>
#include <vector>

int main() {
    {
        ft::pair<int, int> pair(21, 42);

        assert(pair.first == 21);
        assert(pair.second == 42);
    }
    {
        ft::pair<int, ft::pair<std::string, ft::pair<std::set<unsigned int>,
                                                     std::vector<int> > > >
            pair;
        assert(pair.first == int());
        assert(pair.second.first == std::string());
        assert(pair.second.second.first == std::set<unsigned int>());
        assert(pair.second.second.second == std::vector<int>());
    }
    {
        const ft::pair<int, double> pair1(1, 3.41);
        const ft::pair<int, double> pair2(5, 1.41);
        assert(pair1 < pair2);
    }
    {
        const ft::pair<int, double> pair1(1, 3.41);
        const ft::pair<int, double> pair2(1, 6.28);
        assert(pair1 < pair2);
    }
}
