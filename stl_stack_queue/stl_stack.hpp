

#ifndef __YUFC_STL_STACK__
#define __YUFC_STL_STACK__

#include <iostream>
#include <vector>
#include <deque>

namespace yufc
{
    template <class T, class Container = std::deque<T>>
    class stack
    {
    private:
        Container __con;

    public:
        void push(const T &x)
        {
            __con.push_back(x);
        }
        void pop()
        {
            __con.pop_back();
        }
        T &top()
        {
            return __con.back();
        }
        const T &top() const
        {
            return __con.back();
        }
        bool empty() const
        {
            return __con.empty();
        }
        size_t size() const
        {
            return __con.size();
        }
    };
} // namespace yufc

#endif