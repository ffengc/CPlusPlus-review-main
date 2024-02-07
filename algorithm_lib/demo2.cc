

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <list>
#include <set>
#include <chrono>
#include <random>

/* 修改序列操作 */

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
    // copy
    std::list<int> lst1 = {1, 2, 3, 4, 5};
    std::vector<int> arr(lst1.size(), 0); // 要提前扩容，不然就会段错误
    std::copy(lst1.begin(), lst1.end(), arr.begin());
    print(arr);
    // copy_n
    std::vector<int> arr2(4, 0);
    std::copy_n(lst1.begin(), 3, arr2.begin() + 1); // 拷贝到arr2的第二个位置去
    print(arr2);
    // copy_if
    std::vector<int> arr3(5, 0);
    std::copy_if(lst1.begin(), lst1.end(), arr3.begin(), [](int i)
                 { return i <= 3; });
    print(arr3);
    // copy_backward
    std::list<int> lst2 = {1, 2, 3};
    std::vector<int> arr4(lst2.size() + 1, 0);
    std::copy_backward(lst2.begin(), lst2.end(), arr4.end());
    print(arr4); // 0 1 2 3
}

void test2()
{
    // move
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2(arr1.size(), 0);
    std::move(arr1.begin(), arr1.end(), arr2.begin());
    print(arr1); // BUG
    print(arr2);
    // move_backward
    std::vector<int> arr3(arr1.size() + 1, 0);
    std::move_backward(arr1.begin(), arr1.end(), arr3.end());
}

void test3()
{
    // swap
    int a = 10;
    int b = 20;
    std::cout << "a: " << a << ", b: " << b << std::endl;
    std::swap(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
    // swap_ranges
    std::vector<int> s1 = {1, 2, 3, 4, 5};
    std::vector<int> s2 = {10, 20, 30, 40, 50};
    std::swap_ranges(s1.begin(), s1.end(), s2.begin());
    print(s1);
    print(s2);
    // iter_swap
    std::vector<int> s3 = {1, 2, 3};
    std::vector<int> s4 = {3, 2, 1};
    std::iter_swap(s3.begin(), s4.begin());
    print(s3);
    print(s4);
}

struct add
{
    int operator()(int i) { return ++i; }
};
void test4()
{
    // transform
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2(arr1.size(), 0);
    std::transform(arr1.begin(), arr1.end(), arr2.begin(), add());
    print(arr2);                            // 2,3,4,5,6
    std::vector<int> arr3(arr1.size(), 10); // 10,10,10,10,10
    std::vector<int> arr4(arr1.size(), 0);
    std::transform(arr1.begin(), arr1.end(), arr3.begin(), arr4.begin(), std::plus<int>());
    print(arr4); // 11,12,13,14,15
}

void test5()
{
    // replace
    std::vector<int> arr1 = {1, 2, 2, 2, 3, 3, 3, 4, 5};
    std::replace(arr1.begin(), arr1.end(), 2, 10);
    print(arr1);
    // replace_if
    std::vector<int> arr2 = {-1, -1, -2, -4, 0, 2, 3};
    std::replace_if(
        arr2.begin(), arr2.end(), [](int i)
        { return i < 0; },
        100);
    print(arr2); // 把 <0 的换成 100
    // replace_copy
    std::vector<int> arr3 = {1, 2, 2, 2, 3, 3, 3, 4, 5};
    std::vector<int> res(arr3.size(), 0);
    std::replace_copy(arr3.begin(), arr3.end(), res.begin(), 2, 10);
    print(res);
    // replace_copy_if
    std::vector<int> arr4 = {-1, -1, -2, -4, 0, 2, 3};
    std::vector<int> res2(arr4.size(), 0);
    std::replace_copy_if(
        arr4.begin(), arr4.end(), res2.begin(), [](int i)
        { return i < 0; },
        100);
    print(res2);
}

void test6()
{
    // fill
    std::vector<int> arr1(5, 0);
    std::fill(arr1.begin(), arr1.end(), 10);
    print(arr1);
    // fill_n
    std::vector<int> arr2(5, 0);
    std::fill_n(arr2.begin(), 4, 1); // 用4个1去填充
    print(arr2);
}

struct generator
{
    int number = 0;
    int operator()() { return ++number; }
};
void test7()
{
    // generate
    std::vector<int> arr1(5);
    std::generate(arr1.begin(), arr1.end(), generator());
    print(arr1);
}

void test8()
{
    // remove
    std::vector<int> arr1 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
    std::cout << "before calling remove, size: " << arr1.size() << std::endl;
    auto new_end = std::remove(arr1.begin(), arr1.end(), 2);
    std::cout << "after calling remove, size: " << arr1.size() << std::endl;
    print(arr1.begin(), new_end);
    // remove_if
    std::vector<int> arr2 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
    auto new_end2 = std::remove_if(arr2.begin(), arr2.end(), [](int i)
                                   { return i == 2; });
    print(arr2.begin(), new_end2);
}

void test9()
{
    // remove_copy
    std::vector<int> arr1 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
    std::vector<int> arr2(arr1.size());
    auto new_end = std::remove_copy(arr1.begin(), arr1.end(), arr2.begin(), 2);
    print(arr2);
    print(arr2.begin(), new_end);
    // remove_copy_if
    std::vector<int> arr3 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
    std::vector<int> arr4(arr3.size());
    auto new_end2 = std::remove_copy_if(arr3.begin(), arr3.end(), arr4.begin(), [](int i)
                                        { return i == 2; });
    print(arr4.begin(), new_end2);
}

void test10()
{
    // unique
    std::vector<int> arr1 = {1, 2, 2, 3, 3, 4, 3, 2, 5, 5, 8, 5, 9, 10, 2, 10};
    std::unique(arr1.begin(), arr1.end());
    print(arr1);
    // unique_copy
    std::vector<int> arr2 = {1, 2, 2, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 9, 9, 10, 10};
    std::vector<int> res(arr2.size());
    auto it = std::unique_copy(arr2.begin(), arr2.end(), res.begin());
    print(res);
    print(res.begin(), it);
}

void test11()
{
    // reverse
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::reverse(arr1.begin(), arr1.end());
    print(arr1);
    // reverse_copy
    std::vector<int> arr2 = {1, 2, 3, 4};
    std::vector<int> res(arr2.size());
    std::reverse_copy(arr2.begin(), arr2.end(), res.begin());
    print(res);
}

void test12()
{
    // rotate
    std::vector<int> arr1 = {1, 2, 3, 4, 5, 6};
    std::rotate(arr1.begin(), arr1.begin() + 3, arr1.end()); // 让4作第一个元素
    print(arr1);
    // rotate_copy
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6};
    std::vector<int> res(arr2.size());
    std::rotate_copy(arr2.begin(), arr2.begin() + 3, arr2.end(), res.begin()); // 让4作第一个元素
    print(res);
}

void test13()
{
    // random_shuffle
    std::vector<int> arr1 = {1, 2, 3, 4, 5, 6};
    std::random_shuffle(arr1.begin(), arr1.end());
    print(arr1);
    // shuffle
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr2.begin(), arr2.end(), std::default_random_engine(seed));
    print(arr2);
}

int main()
{
    test13();
    return 0;
}