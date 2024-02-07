

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

/* 堆操作 */

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
    // make_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    print(arr);
}

void test2()
{
    // push_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    print(arr);
    arr.push_back(10);
    std::push_heap(arr.begin(), arr.end());
    print(arr);
}

void test3()
{
    // pop_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    std::cout << "before pop: ";
    print(arr);
    std::pop_heap(arr.begin(), arr.end());
    std::cout << "after pop, whole list: ";
    print(arr);
    std::cout << "after pop, heap: ";
    arr.pop_back();
    print(arr);
}

void test4()
{
    // sort_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    print(arr);
    std::sort_heap(arr.begin(), arr.end());
    print(arr);
}

void test5()
{
    // is_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::cout << std::is_heap(arr.begin(), arr.end()) << std::endl;
    std::make_heap(arr.begin(), arr.end());
    std::cout << std::is_heap(arr.begin(), arr.end()) << std::endl;
}

void test6()
{
    // is_heap_until
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    arr.push_back(10);
    print(arr);
    auto it = std::is_heap_until(arr.begin(), arr.end());
    print(it, arr.end());
}

int main()
{
    test6();
    return 0;
}