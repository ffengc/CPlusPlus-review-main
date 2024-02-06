
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <set>

/* 非修改序列操作部分函数 */

void test1()
{
    // all_off
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::cout << std::all_of(arr.begin(), arr.end(), [](int i)
                             { return i % 2 == 0; })
              << std::endl;
    // any_off
    std::vector<int> arr2 = {1, 2, 4, 5};
    std::cout << std::any_of(arr2.begin(), arr2.end(), [](int i)
                             { return i % 3 == 0; })
              << std::endl;
    // none_of
    std::vector<int> arr3 = {1, 2, 3, 4, 5};
    std::cout << std::none_of(arr3.begin(), arr3.end(), [](int i)
                              { return i < 0; })
              << std::endl;
}

void func(int i, int j)
{
    std::cout << "hello world: " << i << ":" << j << std::endl;
}
struct func_class
{
    void operator()(int i)
    {
        std::cout << "hello world: " << i << std::endl;
    }
};
void test2()
{
    auto bind_func = std::bind(func, 5, std::placeholders::_1);
    std::vector<int> arr = {1, 2, 3};
    std::for_each(arr.begin(), arr.end(), bind_func);
    std::for_each(arr.begin(), arr.end(), func_class());
}

void test3()
{
    // find
    std::vector<std::string> arr = {"aa", "bb", "cc", "dd"};
    auto it = std::find(arr.begin(), arr.end(), "bb");
    std::cout << *it++ << std::endl;
    std::cout << *it << std::endl;
    // find_if
    std::unordered_map<int, std::string> hash_map = {{1, "aa"}, {2, "bb"}, {3, "cc"}};
    auto it2 = std::find_if(hash_map.begin(), hash_map.end(), [](const std::pair<int, std::string> p)
                            { return p.second == "bb"; });
    std::cout << it2->first << ":" << it2->second << std::endl;
    // find_if_not
    std::set<int, std::greater<int>> s = {-1, -2, -3, -4, 1, 2, 3, 4};
    auto it3 = std::find_if_not(s.begin(), s.end(), [](int i)
                                { return i > 0; });
    std::cout << *it3++ << std::endl; // 这个应该是-1
    std::cout << *it3 << std::endl;   // 这个应该是-2
    // 原本是升序的，我用了greater，所以是降序
}

void test4()
{
    // find_end
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6};
    std::vector<int> sub_arr = {4, 5, 6};
    auto it = std::find_end(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
    std::cout << "arr[" << it - arr.begin() << "] = " << *it << std::endl;
    // find_first_of
    auto it2 = std::find_first_of(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
    std::cout << "arr[" << it2 - arr.begin() << "] = " << *it2 << std::endl;
}

struct my_pair_cmp
{
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2)
    {
        return p1.first == p2.first;
    }
};
void test5()
{
    // adjacent_find
    std::vector<std::pair<int, int>> arr = {{1, 2}, {2, 2}, {2, 3}, {-1, 2}, {0, 0}, {0, 1}};
    auto it = std::adjacent_find(arr.begin(), arr.end(), my_pair_cmp());
    printf("arr[%d].first = arr[%d].first = %d\n", it - arr.begin(), it - arr.begin() + 1, it->first);
}

void test6()
{
    // count
    std::vector<char> arr = {'a', 'b', 'c', 'd', 'e', 'a'};
    std::cout << std::count(arr.begin(), arr.end(), 'a') << std::endl; // 2
    // count_if
    // 计算小于0的元素的个数
    std::vector<int> arr1 = {-1, 0, 4, 7, -4, 8, -10, 2, 6, 9};
    std::cout << std::count_if(arr1.begin(), arr1.end(), [](int i)
                               { return i < 0; })
              << std::endl; // 3
}

void test7()
{
    // mismatch
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::vector<int> arr2 = {1, 2, 4, 3};
    auto p = std::mismatch(arr1.begin(), arr1.end(), arr2.begin());
    std::cout << "the first mismatched element in to list: " << *(p.first) << ":" << *(p.second) << std::endl;
    // equal
    std::cout << std::equal(arr1.begin(), arr1.end(), arr2.begin()) << std::endl;
    // is_permutation
    std::vector<int> arr3 = {1, 2, 3};
    std::vector<int> arr4 = {2, 1, 3};
    std::cout << std::is_permutation(arr3.begin(), arr3.end(), arr4.begin()) << std::endl;
}

void test8()
{
    // search
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> sub_arr = {2, 3, 4};
    auto it = std::search(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
    std::cout << *it << std::endl;
    // search_n
    std::vector<int> arr2 = {1, 2, 2, 2, 2, 3, 3, 4, 5};
    auto it2 = std::search_n(arr2.begin(), arr2.end(), 3, 2); // 找连续的3个2
    auto it3 = std::search_n(arr2.begin(), arr2.end(), 3, 3); // 找连续的3个3 -- 这个是找不到的
    std::cout << *it2 << std::endl; // 2
    std::cout << *it3 << std::endl; // 0
}

int main()
{
    test8();
    return 0;
}