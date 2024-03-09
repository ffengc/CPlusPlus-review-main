
#include <iostream>
#include "lru_cache.hpp"

void test1()
{
    LRUCache<int, int> lc;
    // LRUCache<int, int, 20> lc2;
    lc.put(1, 1);
    lc.put(2, 2);
    lc.put(3, 3);
    std::cout << lc.size() << std::endl;
    lc.clear();
    std::cout << lc.size() << std::endl;
    lc.put(1, 1);
    lc.put(2, 2);
    lc.put(3, 3);
    std::cout << lc.size() << std::endl;
}

int main()
{
    test1();
    return 0;
}