
#ifndef __YUFC_STL_VECTOR__
#define __YUFC_STL_VECTOR__

#include <string.h>
#include <assert.h>
#include <iostream>
#include <initializer_list>

namespace BagPack
{
    template <class T>
    class vector
    {
    public:
        typedef T *iterator;
        const typedef T *const_iterator;
        iterator begin() { return __start; }
        iterator end() { return __finish; }
        const_iterator begin() const { return __start; }
        const_iterator end() const { return __finish; }

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
        // 支持迭代器区间的构造
        template <class InputIterator>
        vector(InputIterator first, InputIterator last)
            : __start(nullptr), __finish(nullptr), __end_of_storage(nullptr)
        {
            while (first != last)
            {
                push_back(*first++); // 直接push_back会报错, 要记得初始化
            }
        }
        // 支持初始化列表构造
        vector(const std::initializer_list<T> &in_lst)
            : __start(nullptr), __finish(nullptr), __end_of_storage(nullptr)
        {
            typename std::initializer_list<T>::iterator iter = in_lst.begin();
            reserve(in_lst.size());
            while (iter != in_lst.end())
            {
                push_back(*iter++);
            }
        }
        // 支持n个同样的东西构造
        vector(size_t n, const T &val = T())
            : __start(nullptr), __finish(nullptr), __end_of_storage(nullptr)
        {
            /*
                注意：用这个进行构造，有可能会调用到 迭代器区间构造的构造函数里面去
                两个类型都是int的时候就会出错，因为他会认为迭代器构造那个构造更匹配
            */
            reserve(n);
            for (size_t i = 0; i < n; i++)
            {
                push_back(val);
            }
        }
        // 拷贝构造
        vector(const vector<T> &v)
            : __start(nullptr), __finish(nullptr), __end_of_storage(nullptr)
        {
            vector<T> tmp(v.begin(), v.end());
            swap(tmp); // this 和 tmp swap一下
        }
        vector<T> &operator=(const vector<T> &v)
        {
            vector<T> tmp(v.begin(), v.end());
            swap(tmp); // this 和 tmp swap一下
            return *this;
        }
        void swap(vector<T> &v)
        {
            std::swap(__start, v.__start);
            std::swap(__finish, v.__finish);
            std::swap(__end_of_storage, v.__end_of_storage);
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
                    // memcpy(tmp, __start, sizeof(T) * sz); // memcpy是有问题的
                    /*
                        memcpy是有问题的，因为memcpy不会触发自定义类型的拷贝构造！
                        所以如果我们的vector里面存的是内置问题，那是没问题的
                        但是如果我们是自定义类型的时候，memcpy就拷贝不过去了
                    */
                    for (size_t i = 0; i < sz; i++)
                    {
                        tmp[i] = __start[i];
                    }
                    delete[] __start; // 释放旧的空间
                }
                __start = tmp; // 让start指向新的空间
                __finish = __start + sz;
                __end_of_storage = __start + n;
            }
        }
        void resize(size_t n, const T &val = T())
        {
            if (n > capacity())
            {
                reserve(n);
            }
            if (n > size())
            {
                // 初始化填值
                while (__finish < __start + n)
                {
                    *__finish = val;
                    ++__finish;
                }
            }
            else
            {
                __finish = __start + n;
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
        T &front()
        {
            assert(size() > 0);
            return *__start;
        }
        T &back()
        {
            assert(size() > 0);
            return *(__finish - 1);
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
        void pop_back()
        {
            assert(__finish > __start);
            --__finish;
        }
        iterator insert(iterator pos, const T &x)
        {
            assert(pos >= __start && pos <= __finish);
            if (__finish == __end_of_storage)
            {
                size_t length = pos - __start;
                reserve(capacity() == 0 ? 4 : capacity() * 2); // 扩容
                pos = __start + length;                        // 用这两句解决迭代器失效问题！
            }
            // 挪动数据
            iterator end = __finish - 1;
            while (end >= pos)
            {
                *(end + 1) = *end;
                --end;
            }
            *pos = x;
            ++__finish;
            return pos;
        }
        iterator erase(iterator pos)
        {
            /*
                erase迭代器会失效吗？我们实现这个是不会的，因为我们没动空间
                库里会不会呢？库里如果缩容，就会有！
            */
            assert(pos >= __start && pos < __finish);
            iterator begin = pos + 1;
            while (begin < __finish)
            {
                *(begin - 1) = *begin;
                ++begin;
            }
            --__finish;
            return pos;
        }
    };
} // namespace BagPack

#endif