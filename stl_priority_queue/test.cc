

#include <iostream>
#include <algorithm>
#include "stl_priority_queue.hpp"

void test1()
{
    // yufc::priority_queue<int> pq;
    yufc::priority_queue<int> pq;
    pq.push(5);
    pq.push(3);
    pq.push(2);
    pq.push(10);
    pq.push(1);
    pq.push(0);

    while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";
}
void test2()
{
    // std::vector<int> arr = {1, 10, 2, 9, 8, 3, 5, 9, 6, 4};
    // yufc::priority_queue<int> pq(arr.begin(), arr.end());
    yufc::priority_queue<int, std::vector<int>, std::greater<int>> pq = {1, 10, 2, 9, 8, 3, 5, 9, 6, 4};
    while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";
}
bool myfunction (int i,int j) { return (i<j); }
void test3()
{
    // 注意区分sort(), sort()里面是传函数对象，priority_queue是传一个类，不一样的
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    struct myclass
    {
        bool operator()(int i, int j) { return (i < j); }
    };
    std::sort(arr.begin(), arr.end(), myclass());
    std::sort(arr.begin(), arr.end(), myfunction);
    // sort里面要的是一个函数对象，不是仿函数（仿函数是一个类，可以像函数一样调用的类）
    // 所以类重载了()之后，类名()-->就是一个函数对象
}
int main()
{
    test3();
    return 0;
}