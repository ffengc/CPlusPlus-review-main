
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include "stl_map.hpp"
#include "stl_set.hpp"

void test_set1()
{
    yufc::set<int> s;
    s.insert(3);
    s.insert(4);
    s.insert(5);
    auto it = s.begin();
    std::cout << (it != s.end()) << std::endl;
}

void test_map1()
{
    yufc::map<int, int> m;
    m.insert({3, 4});
    m.insert({4, 5});
    m.insert({5, 6});
    m.insert({6, 7});
    auto it = m.begin();
    std::cout << (it != m.end()) << std::endl;
}

template <class k, class v>
std::ostream &operator<<(std::ostream &out, std::pair<k, v> &kv)
{
    out << kv.first << ":" << kv.second << std::endl;
    return out;
}
void test2()
{
    /* 测试迭代器的++ */
    yufc::set<int> s = {1, 3, 3, 3, 3, 3, 3, 6, 7, 2, 4, 9, 10, 0, -1, 2, 3};
    auto it = s.begin();
    while (it != s.end())
    {
        std::cout << *it++ << " ";
        // ++it;
    }
    std::cout << "\n";

    yufc::map<int, int> m = {{1, 2}, {2, 3}, {3, 7}, {3, 5}, {3, 7}, {3, 9}, {-1, 5}, {10, 2}, {0, 1}};
    auto it2 = m.begin();
    while (it2 != m.end())
    {
        std::cout << *it2++ << " ";
    }
    std::cout << "\n";
}
void test3()
{
    // 测试迭代器的--
    // 不知道怎么测试了
}
void test4()
{
    // 测试[]
    yufc::map<int, std::string> Map;
    std::vector<std::string> arr = {"aaa", "bbb", "ccc", "ddd"};
    for (size_t i = 0; i < arr.size(); i++)
        Map.insert({i, arr[i]});
    auto it = Map.begin();
    while (it != Map.end())
    {
        std::cout << it->first << ":" << Map[it->first] << std::endl;
        ++it;
    }
}
void test5()
{
    // 单独测试一下后置++
    yufc::set<int> s = {1, 2, 2};
    auto it = s.begin();
    std::cout << *(it++) << std::endl;
    std::cout << *it << std::endl;
}
int main()
{
    // test_set1();
    // test_map1();
    test5();
    return 0;
}