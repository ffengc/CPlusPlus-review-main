
#include "stl_list.hpp"
#include <iostream>
#include <algorithm>

template <typename T>
void show_lst(yufc::list<T> &lst)
{
    // 这里要记得用引用，因为深拷贝还没写
    typename yufc::list<T>::iterator iter = lst.begin();
    while (iter != lst.end())
    {
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << "\n";
}
void test1()
{
    yufc::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    show_lst(lst);
    std::cout << std::endl;
}
void test2_func(const yufc::list<int> &lst)
{
    auto iter = lst.begin();
    while (iter != lst.end())
    {
        // iter *= 2;
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << '\n';
}
void test2()
{
    yufc::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    lst.push_back(505);
    test2_func(lst);
}
void test3()
{
    // 测试一些push和pop那些
    yufc::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    lst.push_back(505);
    show_lst(lst); // {1,2,3,4,5,505}
    lst.pop_back();
    show_lst(lst); // {1,2,3,4,5}
    lst.pop_front();
    show_lst(lst); // {2,3,4,5}
    lst.push_back(100);
    show_lst(lst); // {2,3,4,5,100}
    lst.push_front(-100);
    show_lst(lst); // {-100,2,3,4,5,100}
}
void test4()
{
    // yufc::list<int> lst = {1, 2, 3, 4, 5, 6};
    // show_lst(lst);
    // auto it = std::find(lst.begin(), lst.end(), 3); // 找到这个3
    // lst.erase(it);
    // show_lst(lst);
}
int main()
{
    test4();
    return 0;
}