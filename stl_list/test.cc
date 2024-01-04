
#include "stl_list.hpp"
#include <iostream>

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

int main()
{
    test1();
    return 0;
}