

#include <iostream>
#include <numeric>
#include <vector>
#include <string>

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

std::string my_strcat(const std::string &s1, const std::string &s2)
{
    return s1 + s2;
}

void test1()
{
    // accumulate
    std::vector<int> arr = {1, 2, 3, 4, 5};
    int res = std::accumulate(arr.begin(), arr.end(), 0); // 从0开始累加
    std::cout << res << std::endl;
    std::vector<std::string> str_arr = {"aa", "bb", "cc"};
    std::string init = "";
    auto res2 = std::accumulate(str_arr.begin(), str_arr.end(), init, my_strcat);
    std::cout << res2 << std::endl;
}

void test2()
{
    // adjacent_difference
    std::vector<int> arr = {0, 2, 3, 4, 5};
    std::vector<int> res(arr.size());
    std::adjacent_difference(arr.begin(), arr.end(), res.begin());
    print(res);
}

void test3()
{
    // inner_product
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2 = {1, 2, 3, 4, 5};
    std::cout << std::inner_product(arr1.begin(), arr1.end(), arr2.begin(), 0) << std::endl;
}

std::string my_strcat2(const std::string &s1, const std::string &s2)
{
    return s1 + s1 + s2 + s2;
}
void test4()
{
    // partial_sum
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> res1(arr1.size());
    std::partial_sum(arr1.begin(), arr1.end(), res1.begin());
    print(res1);
    std::vector<std::string> arr2 = {"a", "b", "c"};
    std::vector<std::string> res2(arr1.size());
    std::partial_sum(arr2.begin(), arr2.end(), res2.begin(), my_strcat2);
    print(res2);
}

void test5()
{
    std::vector<int> arr1(5);
    std::iota(arr1.begin(), arr1.end(), 1);
    print(arr1);
}

int main()
{
    test5();
    return 0;
}