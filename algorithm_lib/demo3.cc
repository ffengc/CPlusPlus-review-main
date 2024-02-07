

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

/* 分组操作 */

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
    // is_partitioned
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::cout << std::is_partitioned(arr1.begin(), arr1.end(), [](int i)
                                     { return i <= 3; })
              << std::endl;
    // partition 和 stable_partition
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
    // std::partition(arr2.begin(), arr2.end(), [](int i)
    //                { return i % 2 == 0; });
    std::stable_partition(arr2.begin(), arr2.end(), [](int i)
                          { return i % 2 == 0; });
    print(arr2);
}

void test2()
{
    // partition_copy
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> odd(arr.size());  // 奇数
    std::vector<int> even(arr.size()); // 偶数
    auto p = std::partition_copy(arr.begin(), arr.end(), odd.begin(), even.begin(), [](int i)
                                 { return i % 2 == 1; });
    print(odd.begin(), p.first);
    print(even.begin(), p.second);
}

void test3()
{
    // partition_point
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    auto is_odd = [](int i)
    { return i % 2 == 1; };
    if (!std::is_partitioned(arr.begin(), arr.end(), is_odd))
        assert(false);
    auto point = std::partition_point(arr.begin(), arr.end(), is_odd);
    print(arr.begin(), point);
    print(point, arr.end());
}

int main()
{
    test3();
    return 0;
}