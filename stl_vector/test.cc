
#include "stl_vector.hpp"
#include <algorithm>
#include <list>

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
void test2_func(const BagPack::vector<int> &v)
{
    // 如果没写拷贝，就要记得带上 &，不然就会出问题
    BagPack::vector<int>::const_iterator it = v.begin();
    while (it != v.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}
void test2()
{
    BagPack::vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    test2_func(arr);
}
void test3()
{
    BagPack::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    // v.push_back(5); // 有这一行就能跑通，如果没有就跑不通？为什么？

    // 遍历
    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    auto p = std::find(v.begin(), v.end(), 3);
    if (p != v.end())
    {
        v.insert(p, 66); // 在3的前面插入一个30
        /*
            这个insert可能会发生扩容！
            扩完容，这个p还有效吗？
            vector的空间已经到别的地方去了，你的p还在原地
            那p真永远都不可能等于 v.end() 了
            因为 v.end() 已经到别的地方去了
            这个就是迭代器失效问题！
        */
        // ok 我们在insert里面更新了pos，那insert完就可以用这个p了吗？
        // 可以 继续 cout << *p; 或者 v.insert(p, 55); 这样吗？
        // 不可以！insert里面修改的pos和外面的p有关系吗？没关系！形式参数不影响实际参数！
        // 为什么不把参数改成引用，让它浅拷贝呢？不要，因为库里面就是深拷贝，库这样实现是有它自己的原因的
        // 一个简单的例子，v.insert(v.begin(), 0); 如果改成引用还得了？
        // 首先v.begin()是肯定不能改的，也不给改！如果参数改成引用 v.insert(v.begin(), 0);
        // 肯定是编译不通过的，因为v.begin()这个函数返回迭代器，是传值返回，会发生拷贝，产生
        // 临时对象，临时对象具有常性
        // 记住，insert/erase后，这个迭代器，不要再用了！！
    }

    // 遍历
    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test4()
{
    BagPack::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    BagPack::vector<int>::iterator it_p = std::find(v.begin(), v.end(), 3);
    v.erase(it_p);

    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test5()
{
    BagPack::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    // 删除所有的偶数 -- 这里如果处理不当也会遇到失效问题
    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    BagPack::vector<int>::iterator iter = v.begin();
    while (iter != v.end())
    {
        if (*iter % 2 == 0)
        {
            iter = v.erase(iter); // 更新一下迭代器
        }
        else
        {
            iter++;
        }
    }

    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test6()
{
    // 把深拷贝完善一下
    // 迭代器区间的构造
    std::list<int> lst = {1, 3, 5, 7, 9};
    BagPack::vector<int> v(lst.begin(), lst.end());
    for (const auto &e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    BagPack::vector<int> v2;
    v2 = v;
    for (const auto &e : v2)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test7()
{
    // 初始化列表初始化
    BagPack::vector<int> arr = {1, 3, 5, 7, 9, 11};
    for (const auto &e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test8()
{
    BagPack::vector<std::string> arr = {"aa", "bb", "cc"};
    for (const auto &e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test9()
{
    BagPack::vector<std::string> arr(3, "aaa");
    for (const auto &e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void test10()
{
    // 测试resize
    BagPack::vector<int> v;
    v.resize(10, 0);
    for (const auto e : v)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    BagPack::vector<int> v1 = {1, 2, 3, 4, 5};
    v1.resize(10, 0);
    for (const auto e : v1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    v1.resize(20, 20);
    for (const auto e : v1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    v1.resize(3);
    for (const auto e : v1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
BagPack::vector<BagPack::vector<int>> test11()
{
    // 写一个vector的最后一个要解决的大问题
    BagPack::vector<BagPack::vector<int>> vv;
    vv.push_back({1, 2, 3, 4});
    vv.push_back({1, 2, 3, 4});
    vv.push_back({1, 2, 3});
    vv.push_back({1, 2, 3});
    vv.push_back({1, 2, 3});
    vv.push_back({1, 2, 3});
    vv.push_back({1, 2, 3});
    return vv; // 传值返回就有问题了！
    // 因为里面变成一个浅拷贝了
}
int main()
{
    BagPack::vector<BagPack::vector<int>> vv = test11();
    for (int i = 0; i < vv.size(); i++)
    {
        for (int j = 0; j < vv[i].size(); j++)
        {
            std::cout << vv[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
