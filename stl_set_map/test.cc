
#include <iostream>
#include "stl_map.hpp"
#include "stl_set.hpp"

void test_set1()
{
    yufc::set<int> s;
    s.insert(3);
    s.insert(4);
    s.insert(5);
    auto it = s.begin();
    std::cout << (it != s.end()) << std::endl;
}

void test_map1()
{
    yufc::map<int, int> m;
    m.insert({3, 4});
    m.insert({4, 5});
    m.insert({5, 6});
    m.insert({6, 7});
    auto it = m.begin();
    std::cout << (it != m.end()) << std::endl;
}

int main()
{
    test_set1();
    test_map1();
    return 0;
}