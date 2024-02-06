

#include <random>
#include <iostream>
#include <functional>

void test1()
{
    // 小demo
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 6);
    std::cout << distribution(generator) << std::endl;
    auto random_function = std::bind(distribution, generator);
    std::cout << random_function() << std::endl;
}

int main()
{
    test1();
    return 0;
}