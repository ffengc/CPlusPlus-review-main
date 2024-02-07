

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

/* 排序操作 */

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
    // sort
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::sort(arr.begin(), arr.end());
    print(arr);
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    print(arr);
}

void test2()
{
    // stable_sort
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::stable_sort(arr.begin(), arr.end());
    print(arr);
    std::stable_sort(arr.begin(), arr.end(), std::greater<int>());
    print(arr);
}

void test3()
{
    // partial_sort
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::partial_sort(arr.begin(), arr.begin() + 4, arr.end());
    print(arr);
}

void test4()
{
    // partial_sort_copy
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::vector<int> res(3);
    std::partial_sort_copy(arr.begin(), arr.end(), res.begin(), res.end(), std::greater<int>());
    print(res); // 10 9 8
}

void test5()
{
    // is_sorted
    std::vector<int> arr1 = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << std::is_sorted(arr1.begin(), arr1.end()) << std::endl; // 0
    std::cout << std::is_sorted(arr2.begin(), arr2.end()) << std::endl; // 1
}

void test6()
{
    // is_sorted_until
    std::vector<int> arr1 = {1, 2, 3, 4, 5, -1, -2, 0};
    auto it = std::is_sorted_until(arr1.begin(), arr1.end());
    print(arr1.begin(), it);
    print(it, arr1.end());
}

void test7()
{
    // nth_element
    std::vector<int> arr1 = {1, 2, 3, 4, 5, -1, -2, 0};
    std::nth_element(arr1.begin(), arr1.end() - 1, arr1.end()); // 排列之后最后一个元素一定是5
    print(arr1);
}

int main()
{
    test7();
    return 0;
}