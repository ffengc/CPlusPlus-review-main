

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

/* 其他函数 */

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
    // lexicographical_compare
    std::vector<int> arr1 = {1, 2, -1, 1, 1, 1, 1};
    std::vector<int> arr2 = {1, 2, 1};
    std::cout << std::lexicographical_compare(arr1.begin(), arr1.end(), arr2.begin(), arr2.end()) << std::endl;
}

void test2()
{
    // next_permutation
    std::vector<int> arr = {1, 2, 3, 4, 5};
    print(arr);
    std::cout << std::next_permutation(arr.begin(), arr.end()) << std::endl; // 是否有字典序更大的排列
    print(arr);
    std::vector<int> arr2 = {5, 4, 3};
    std::cout << std::next_permutation(arr2.begin(), arr2.end()) << std::endl; // 是否有字典序更大的排列
}

void test3()
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::cout << std::prev_permutation(arr.begin(), arr.end()) << std::endl;
}

int main()
{
    test3();
    return 0;
}