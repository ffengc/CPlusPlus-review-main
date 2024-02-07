

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

/* 合并 */

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
    // merge
    std::vector<int> arr1 = {1, 3, 5, 7};
    std::vector<int> arr2 = {2, 4, 9, 11};
    std::vector<int> res(arr1.size() + arr2.size());
    std::merge(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res);
}

void test2()
{
    // inplace_merge
    std::vector<int> arr1 = {1, 3, 5, 7};
    std::vector<int> arr2 = {2, 4, 9, 11};
    std::vector<int> before_inplace_merge = arr1;
    for (auto it = arr2.begin(); it != arr2.end(); it++)
        before_inplace_merge.push_back(*it);
    std::cout << "before_inplace_merge: ";
    print(before_inplace_merge);
    std::inplace_merge(before_inplace_merge.begin(), before_inplace_merge.begin() + arr1.size(), before_inplace_merge.end());
    std::cout << "after_inplace_merge: ";
    print(before_inplace_merge);
}

void test3()
{
    // includes
    std::vector<int> sub_arr = {1, 3, 5, 7};
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    std::cout << std::includes(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end()) << std::endl;
}

void test4()
{
    // set_union
    std::vector<int> arr1 = {1, 2, 3, 5, 7, 9, 11, 13};
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> res(arr1.size() + arr2.size());
    auto it = std::set_union(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res.begin(), it);
}

void test5()
{
    // set_intersection
    std::vector<int> arr1 = {1, 2, 3, 5, 7, 9, 11, 13};
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> res(std::max(arr1.size(), arr2.size()));
    auto it = std::set_intersection(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res.begin(), it);
}

void test6()
{
    // set_difference
    std::vector<int> arr1 = {1, 2, 3, 5, 7, 9, 11, 13};
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> res(std::max(arr1.size(), arr2.size()));
    auto it = std::set_difference(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res.begin(), it);
}

void test7()
{
    // set_symmetric_difference
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::vector<int> arr2 = {2, 3, 4, 5};
    std::vector<int> res(3);
    auto it = std::set_symmetric_difference(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res.begin(), it); // 1 5
}

int main()
{
    test7();
    return 0;
}