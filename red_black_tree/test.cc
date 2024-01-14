

#include "rb_tree.hpp"
#include <random>

void test1()
{
    int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    rb_tree<int, int> t1;
    for (auto e : arr)
    {
        t1.Insert(std::make_pair(e, e));
    }
    t1.InOrder();
    std::cout << ((t1.CheckValidation() == 1) ? "true" : "false") << std::endl;
}
void test2()
{
    size_t N = 10000;
    rb_tree<int, int> t1;
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(0, 100000);
    e.seed(time(0));
    for (size_t i = 0; i < N; i++)
    {
        t1.Insert(std::make_pair(u(e), i));
    }
    t1.InOrder();
    std::cout << ((t1.CheckValidation() == 1) ? "true" : "false") << std::endl;
}
int main()
{
    test2();
    return 0;
}