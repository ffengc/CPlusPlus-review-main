
#include "stl_list.hpp"
#include <iostream>
#include <algorithm>

template <class value_type>
std::ostream &operator<<(std::ostream &out, const yufc::list<value_type> &lst)
{
    // 这里要记得用引用，因为深拷贝还没写
    auto iter = lst.begin();
    while (iter != lst.end())
    {
        out << *iter << " ";
        ++iter;
    }
    // out << "\n";
    return out;
}

void test1()
{
    yufc::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    std::cout << lst << std::endl;
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
    // show_lst(lst); // {1,2,3,4,5,505}
    lst.pop_back();
    // show_lst(lst); // {1,2,3,4,5}
    lst.pop_front();
    // show_lst(lst); // {2,3,4,5}
    lst.push_back(100);
    // show_lst(lst); // {2,3,4,5,100}
    lst.push_front(-100);
    // show_lst(lst); // {-100,2,3,4,5,100}
}
void test4()
{
    // 深拷贝
    yufc::list<int> lst = {1, 2, 3, 4, 5, 6, 7};
    // yufc::list<int> lst_copy = lst;
    // lst_copy.push_back(10);
    std::cout << lst << std::endl;
    // show_lst(lst_copy);
    /*
        为什么没有崩溃（没有写深拷贝的时候）：因为我们没写析构，写了析构就会崩溃了，因为会析构两次
    */
    // 测试 clear()
    // lst.clear();
    std::cout << lst << std::endl;
    yufc::list<int> lst_copy = lst; // 写好了析构，就会崩溃了
    yufc::list<int> lst_copy2;
    lst_copy2 = lst;
    std::cout << lst_copy2 << std::endl;
}
void test5()
{
    // 测试
}
int main()
{
    test4();
    return 0;
}