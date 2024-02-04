
#include <string>
#include <iostream>
#include "union_find_disjoint_set.hpp"

void test1()
{
    std::string a[] = {"zhangsan", "lisi", "wangwu", "zhaoliu"};
    union_find_disjoint_set<std::string> ufs(a, 4);
}
int main()
{
    test1();
    return 0;
}