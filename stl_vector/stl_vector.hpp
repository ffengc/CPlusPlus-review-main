
#ifndef __YUFC_STL_VECTOR__
#define __YUFC_STL_VECTOR__

#include <string.h>
#include <assert.h>
#include <iostream>

namespace BagPack
{
    template <class T>
    class vector
    {
    public:
        typedef T *iterator;
        iterator begin() { return __start; }
        iterator end() { return __finish; }

    private:
        iterator __start;
        iterator __finish;
        iterator __end_of_storage;

    public:
        vector()
            : __start(nullptr), __finish(nullptr), __end_of_storage(nullptr) {}
        ~vector()
        {
            delete[] __start;
            __start = __finish = __end_of_storage = nullptr;
        }

    public:
        size_t capacity() const
        {
            return __end_of_storage - __start;
        }
        size_t size() const
        {
            return __finish - __start;
        }
        void reserve(size_t n)
        {
            if (n > capacity())
            {
                T *tmp = new T[n];
                size_t sz = size(); // 先把大小记住，因为等下__start指向新空间，size()就找不到了
                if (__start)
                {
                    // 如果旧空间不是空，就要把旧的内容拷贝到新空间上去
                    memcpy(tmp, __start, sizeof(T) * sz);
                    delete[] __start; // 释放旧的空间
                }
                __start = tmp; // 让start指向新的空间
                __finish = __start + sz;
                __end_of_storage = __start + n;
            }
        }

    public:
        T &operator[](size_t pos)
        {
            assert(pos < size());
            return __start[pos];
        }
        const T &operator[](size_t pos) const
        {
            assert(pos < size());
            return __start[pos];
        }

    public:
        void push_back(const T &x)
        {
            if (__finish == __end_of_storage)
            {
                reserve(capacity() == 0 ? 4 : capacity() * 2);
            }
            *__finish = x;
            ++__finish; // 注意，__finish是最后一个位置的下一个位置
        }
    };
} // namespace BagPack

#endif