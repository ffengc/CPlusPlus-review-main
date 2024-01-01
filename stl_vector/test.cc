
#include "stl_vector.hpp"

void test1()
{
    BagPack::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    for (int i = 0; i < v1.size(); i++)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << std::endl;
    // 用迭代器试一下
    BagPack::vector<int>::iterator it = v1.begin();
    while (it != v1.end())
    {
        std::cout << *it++ << " ";
    }
    std::cout << std::endl;
    // 用范围for遍历一下
    for (const auto &e : v1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test1();
    return 0;
}
