

#ifndef __YUFC_STL_QUEUE__
#define __YUFC_STL_QUEUE__

#include <deque>

namespace yufc
{
    template <class T, class Container = std::deque<T>>
    class queue
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
            __con.pop_front();
        }
        T &back()
        {
            return __con.back();
        }
        T &front()
        {
            return __con.front();
        }
        const T &back() const
        {
            return __con.back();
        }
        const T &front() const
        {
            return __con.front();
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