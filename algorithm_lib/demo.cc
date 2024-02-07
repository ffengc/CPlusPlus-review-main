

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <list>
#include <set>
#include <chrono>
#include <random>
#include <assert.h>

/* 二分查找 */

template <class container_type>
void print(container_type con)
{
    auto first = con.begin();
    auto last = con.end();
    while (first != last)
        std::cout << *first++ << " ";
    std::cout << "\n";
}
template <class iterator_type>
void print(iterator_type first, iterator_type last)
{
    while (first != last)
        std::cout << *first++ << " ";
    std::cout << "\n";
}

void test1()
{
    // lower_bound 和 upper_bound
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    if (!std::is_sorted(arr.begin(), arr.end()))
        assert(false);
    auto it = std::lower_bound(arr.begin(), arr.end(), 3);
    print(it, arr.end());
    auto it2 = std::upper_bound(arr.begin(), arr.end(), 3);
    print(it2, arr.end());
}

void test2()
{
    // equal_range
    std::vector<int> arr = {1, 2, 3, 3, 3, 4, 5, 6};
    auto p = std::equal_range(arr.begin(), arr.end(), 3); // 找到3的区间
    // 因为序列是有序的，所以同样的数字肯定都放在一起
    print(p.first, p.second);
}

void test3()
{
    std::vector<int> arr = {1, 2, 3, 3, 3, 4, 5, 6};
    std::cout << std::binary_search(arr.begin(), arr.end(), 4) << std::endl;
    std::cout << std::binary_search(arr.begin(), arr.end(), 10) << std::endl;
}

int main()
{
    test3();
    return 0;
}