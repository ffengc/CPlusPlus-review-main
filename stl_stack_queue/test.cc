

#include "stl_stack.hpp"
#include "stl_queue.hpp"
#include <iostream>
#include <vector>

void test1()
{
    // yufc::stack<int, std::vector<int>> st;
    yufc::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    while (!st.empty())
    {
        std::cout << st.top() << std::endl;
        st.pop();
    }
    st.push(4);
    st.push(3);
    st.push(2);
    st.push(1);
    while (!st.empty())
    {
        std::cout << st.top() << std::endl;
        st.pop();
    }
}
void test2()
{
    yufc::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    while (!q.empty())
    {
        std::cout << q.front() << std::endl;
        q.pop();
    }
}
int main()
{
    test2();
    return 0;
}