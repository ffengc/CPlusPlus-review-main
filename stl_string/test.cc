

#include "stl_string.hpp"

void Test1()

{
    BagPack::string s1("hello world");
    BagPack::string s2;

    std::cout << s1.c_str() << std::endl;
    std::cout << s2.c_str() << std::endl;

    for (size_t i = 0; i < s1.size(); i++)
    {
        s1[i] = 'a';
        std::cout << s1[i] << " ";
    }
    std::cout << std::endl;
}
void Test2()
{
    BagPack::string s1("hello Linux");
    BagPack::string s2;
    // 用迭代器迭代
    BagPack::string::iterator it = s1.begin();
    while (it != s1.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
    // 范围for也是一样的
    for (const auto &e : s1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
void Test3()
{
    // 测试深浅拷贝
    BagPack::string s1("hello Linux");
    BagPack::string s2(s1);
    std::cout << s2.c_str() << std::endl;
    // 如果不写拷贝构造，这里肯定是会崩溃的
    // 如果不写拷贝构造，编译器默认生成一个拷贝构造（浅拷贝），两个对象就会指向同一空间
    // 所以最后就会被释放两次，第一个释放之后，第二个再去释放，直接出问题

    BagPack::string s3;
    s3 = s1;
    std::cout << s3.c_str() << std::endl;
    s1 = s1;
    std::cout << s1.c_str() << std::endl;

    // 区别 s1.swap(s2) 和 swap(s1, s2)
    // swap(s1, s2) 的代价是很大的
}
void Test4()
{
    // 测试push_back等
    BagPack::string s1("hello Linux");
    BagPack::string s2(s1);
    s1 += 'x';
    std::cout << s1.c_str() << std::endl;
    // s1.append(" hello world  adk fja;ds fjk;a sdjfk; asd;jf ");
    s1 += " hello world  adk fja;ds fjk;a sdjfk; asd;jf ";
    std::cout << s1.c_str() << std::endl;
}
void Test5()
{
    // 测试insert
    BagPack::string s1 = "hello Linux";
    // s1.insert(0, '1');
    // s1.insert(1, '2');
    // std::cout << s1.c_str() << std::endl;

    s1.insert(s1.size(), " hello Linux");
    std::cout << s1.c_str() << std::endl;
    s1.insert(0, "hello Linux ");
    std::cout << s1.c_str() << std::endl;
}
void Test6()
{
    // 测试erase
    BagPack::string s1 = "hello Linux";
    s1.erase(2, BagPack::string::npos);
    std::cout << s1.c_str() << std::endl;
}
void Test7()
{
    BagPack::string s1;
    std::cin >> s1;
    std::cout << s1 << std::endl;
}
void Test8()
{
    // 测试find和substr等
    BagPack::string s1("0123456789");
    size_t pos = s1.find("12345");
    std::cout << BagPack::string(s1.substr(pos, 5).c_str()) << std::endl;
}
int main()
{
    Test8();
    return 0;
}