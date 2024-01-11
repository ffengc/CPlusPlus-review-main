

#ifndef __YUFC_STL_PRIORITY_QUEUE__
#define __YUFC_STL_PRIORITY_QUEUE__

#include <vector>
#include <initializer_list>

namespace yufc
{
    template <class T, class Container = std::vector<T>, class Compare = std::less<T>>
    /*
        T: value_type
        Container: adapter适配器
        Compare: 比较的仿函数 (less是大堆，greater是小堆)
    */
    class priority_queue
    {
    private:
        Container __con;

    public:
        priority_queue() {}
        template <class iterator_type>
        void __initialize_by_iterator(iterator_type first, iterator_type last)
        {
            // 向下调整建堆可以做到O(n), 向上调整建堆O(nlogn)
            while (first != last)
            {
                // 所以这里不要直接push
                // 先push_back到__con里面去
                __con.push_back(*first);
                first++;
            }
            // 建堆
            // 用int，避免到-1的时候出问题
            for (int i = (__con.size() - 1 - 1) / 2; i >= 0; i--)
            {
                __adjust_down(i);
            }
        }
        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last)
        {
            __initialize_by_iterator(first, last);
        }
        priority_queue(const std::initializer_list<T> &init_lst)
        {
            auto first = init_lst.begin();
            auto last = init_lst.end();
            __initialize_by_iterator(first, last);
        }

    private:
        void __adjust_up(size_t child)
        {
            Compare com;
            size_t parent = (child - 1) / 2;
            while (child > 0)
            {
                // if (__con[child] > __con[parent])
                if (com(__con[parent], __con[child]))
                {
                    std::swap(__con[child], __con[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }
        void __adjust_down(size_t parent)
        {
            Compare com;
            // 最多高度次 logN
            size_t child = parent * 2 + 1; // 先找左孩子
            while (child < __con.size())
            {
                // 找较大的孩子
                if (child + 1 < __con.size() && com(__con[child], __con[child + 1]))
                {
                    ++child; // 右孩子
                }
                // 看看是否需要调整
                // if (__con[child] > __con[parent])
                if (com(__con[parent], __con[child]))
                {
                    std::swap(__con[child], __con[parent]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                    break;
            }
        }

    public:
        void push(const T &x)
        {
            __con.push_back(x);
            __adjust_up(__con.size() - 1);
        }
        void pop()
        {
            std::swap(__con[0], __con[__con.size() - 1]);
            __con.pop_back();
            __adjust_down(0);
        }

    public:
        const T &top() const
        {
            // 堆顶
            return __con[0];
        }
        bool empty() const
        {
            return __con.empty();
        }
        bool size() const
        {
            return __con.size();
        }
    };
} // namespace yufc

#endif