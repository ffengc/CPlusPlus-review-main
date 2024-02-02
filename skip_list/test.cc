

#include <map>
#include "skip_list.hpp"

void show_list(const yufc::skip_list<int, int> &sl)
{
    for (const auto &e : sl)
    {
        std::cout << e.first << ":" << e.second << std::endl;
    }
}

void test1()
{
    yufc::skip_list<int, int> sl;
    sl.insert({1, 2});
    sl.insert({20, 3});
    sl.insert({3, 4});
    sl.insert({-1, 4});
    sl.insert({5, 4});
    sl.insert({6, 4});
    sl.insert({8, 4});

    auto iter = sl.begin();
    while (iter != sl.end())
    {
        std::cout << iter->first << ":" << iter->second << std::endl;
        iter++;
    }
}
void test2()
{
    std::map<int, int> m;
    m.insert({1, 2});
    m.insert({20, 3});
    m.insert({3, 4});
    m.insert({-1, 4});
    m.insert({5, 4});
    m.insert({6, 4});
    m.insert({8, 4});
    auto iter = m.begin();
}
void test3()
{
    std::vector<std::pair<int, int>> arr = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    yufc::skip_list<int, int> sl(arr.begin(), arr.end());
    for (const auto &e : sl)
    {
        std::cout << e.first << ":" << e.second << std::endl;
    }
    std::cout << sl.empty() << std::endl;
    sl.clear();
    for (const auto &e : sl)
    {
        std::cout << e.first << ":" << e.second << std::endl;
    }
    std::cout << sl.empty() << std::endl;
}
void test4()
{
    yufc::skip_list<int, int> sl = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    auto res = sl.find(10);
    std::cout << "res: " << res.first << " is_found: " << ((res.second == true) ? "true" : "false") << std::endl;
    std::cout << "size: " << sl.size() << std::endl;
    sl.erase(3);
    std::cout << "size: " << sl.size() << std::endl;
    sl.erase(10);
    std::cout << "size: " << sl.size() << std::endl;
}
void test5()
{
    yufc::skip_list<int, int> sl1 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    yufc::skip_list<int, int> sl2;
    sl2 = sl1;
    show_list(sl1);
    std::cout << " --- " << std::endl;
    show_list(sl2);
}
int main()
{
    // test1();
    test5();
    return 0;
}