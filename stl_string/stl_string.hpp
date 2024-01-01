
#ifndef __YUFC_STL_STRING__
#define __YUFC_STL_STRING__

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

namespace BagPack
{
    class string
    {
    private:
        char *__str;
        size_t __size;
        size_t __capacity;

    public:
        // static在类内声明，在类外定义
        // 当然如果加了const就能直接在类里面给缺省，这也是很抽象的一个地方
        static size_t npos;

    public:
        string(const char *str = "")
        {
            // 动态开辟空间
            __size = strlen(str);
            __capacity = __size;
            __str = new char[__capacity + 1];
            strcpy(__str, str);
        }
        ~string()
        {
            delete[] __str;
            __str = nullptr;
            __size = __capacity = 0;
        }
#if false
        // 这个其实是传统写法
        string(const string &s)
            : __str(new char[s.__capacity + 1]), __size(s.__size), __capacity(s.__capacity)
        {
            strcpy(__str, s.__str);
        }
        string &operator=(const string &s)
        {
            if (this == &s)
            {
                // 一定要处理自己给自己赋值的问题
                // 不然一上来就delete了自己，后面怎么搞都是屯屯屯屯屯了
                return *this;
            }
            char *tmp = new char[s.__capacity + 1]; // 指向新空间
            strcpy(tmp, s.__str);
            delete[] __str; // 释放自己的
            __str = tmp;
            __size = s.__size;
            __capacity = s.__capacity;
            return *this;
        }
#endif
        void swap(string &tmp)
        {
            std::swap(__str, tmp.__str);
            std::swap(__size, tmp.__size);
            std::swap(__capacity, tmp.__capacity);
        }
        // 现代写法
        string(const string &s)
            : __str(nullptr), __size(0), __capacity(0)
        {
            string tmp(s.__str); // 我直接调用构造函数
            swap(tmp);
            /*
                这个函数如果不写初始化列表也是有问题的
                因为刚构造的__str, size这些都是随机的
                如果交换给tmp后，tmp是要释放的，让tmp去释放一些抽象东西是不行的
                所以初始化列表初始化一下，给些正常东西换给tmp
            */
        }
        string &operator=(string &s)
        {
            // if (this == &s)
            //     return *this;
            // string tmp(s); // 调用一下拷贝构造即可
            // swap(tmp);     // this 和 tmp换
            swap(s);
            return *this;
        }

    public:
        // 流插入流提取记得要在类外实现，不然this指针抢第一个位置了
    public:
        // 定义迭代器
        typedef char *iterator; // 在string里面就是指针
        typedef const char *const_iterator;
        iterator begin()
        {
            return __str;
        }
        iterator end()
        {
            return __str + __size;
        }
        const_iterator begin() const
        {
            return __str;
        }
        const_iterator end() const
        {
            return __str + __size;
        }

    public:
        const char *c_str()
        {
            return __str;
        }
        size_t size() const
        {
            return __size;
        }
        char &operator[](size_t pos)
        {
            // operator[]要返回引用，因为我们是可以通过[]来修改字符串的
            assert(pos < __size);
            return __str[pos];
        }
        const char &operator[](size_t pos) const
        {
            // 这个是只读的
            assert(pos < __size);
            return __str[pos];
        }
        void clear()
        {
            __str[0] = '\0';
            __size = 0;
        }

    public:
        void reserve(size_t n)
        {
            // 这个函数还是很重要的 -- 功能就是改变capacity
            if (n <= __capacity)
            {
                // 如果要的比现在小的直接返回
                return;
            }
            char *tmp = new char[n + 1]; // 注意这里是n+1
            strcpy(tmp, __str);
            delete[] __str;
            __str = tmp;
            __capacity = n; // __size没有变
        }
        void resize(size_t n, char ch = '\0')
        {
            if (n > __size)
            {
                // 插入数据
                reserve(n);
                for (size_t i = __size; i < n; i++)
                {
                    __str[i] = ch;
                }
                __str[n] = '\0';
                __size = n;
            }
            else
            {
                // 删除数据
                __str[n] = '\0';
                __size = n;
            }
        }
        void push_back(char ch)
        {
            // 如果满了先reserve
            if (__size == __capacity)
            {
                reserve(__capacity == 0 ? 4 : __capacity * 2);
            }
            __str[__size] = ch;
            __size++;
            __str[__size] = '\0'; // 记得加入\0
        }
        void append(const char *str)
        {
            size_t len = strlen(str);
            if (__size + len > __capacity)
            {
                reserve(__size + len);
            }
            strcpy(__str + __size, str); // 拷贝过去就行了，不过往后挪一点而已
            __size += len;
            // cap不用动，reserve会自己动
        }
        string &operator+=(char ch)
        {
            push_back(ch);
            return *this;
        }
        string &operator+=(const char *str)
        {
            append(str);
            return *this;
        }
        string &insert(size_t pos, char ch)
        {
            // push_back那些都可以复用这些
            assert(pos <= __size && pos >= 0);
            if (__size == __capacity)
            {
                reserve(__capacity == 0 ? 4 : __capacity * 2);
            }
            // 挪动数据
            size_t end = __size + 1;
            while (end > pos)
            {
                __str[end] = __str[end - 1];
                --end; // 这里注意，不会到-1的！会变成很大的数 -- 会有越界访问
                /*
                    解决这个的方法，可以把pos先强转成int先
                    第二个方法就是size_t end = __size + 1
                    然后while里面 end > pos , 下面是 把end-1的挪到end上
                */
            }
            __str[pos] = ch;
            ++__size;
            return *this;
        }
        string &insert(size_t pos, const char *str)
        {
            assert(pos <= __size && pos >= 0);
            size_t len = strlen(str);
            if (__size + len > __capacity)
            {
                reserve(__size + len);
            }
            // 挪动数据
            size_t end = __size + len;
            while (end >= pos + len) // 注意这里的end>=pos+len
            {
                __str[end] = __str[end - len];
                end--;
            }
            strncpy(__str + pos, str, len);
            __size += len;
            return *this;
        }
        void erase(size_t pos, size_t len = npos)
        {
            assert(pos < __size && pos >= 0);
            if (len == npos || pos + len >= __size)
            {
                __str[pos] = '\0';
                __size = pos;
            }
            else
            {
                strcpy(__str + pos, __str + pos + len); // 要检查清楚，这样会不会覆盖内存，检查清楚是前重叠还是后重叠
                __size -= len;
            }
        }
        size_t find(char ch, size_t pos = 0) const
        {
            assert(pos < __size && pos >= 0);
            for (size_t i = pos; i < __size; i++)
            {
                if (ch == __str[i])
                    return i;
            }
            return npos;
        }
        size_t find(const char *sub, size_t pos = 0) const
        {
            assert(pos < __size && pos >= 0);
            assert(sub);
            const char *ptr = strstr(__str + pos, sub);
            if (ptr == nullptr)
                return npos;
            else
                return (ptr - __str);
        }
        string substr(size_t pos, size_t len = npos) const
        {
            assert(pos < __size && pos >= 0);
            size_t realLen = len;
            if (len == npos || pos + len > __size)
            {
                realLen = __size - pos;
            }
            string sub;
            for (size_t i = 0; i < realLen; i++)
            {
                sub += __str[pos + i];
            }
            return sub;
        }

    public:
        bool operator>(const string &s) const
        {
            return strcmp(__str, s.__str) > 0;
        }
        bool operator==(const string &s) const
        {
            return strcmp(__str, s.__str) == 0;
        }
        bool operator>=(const string &s) const
        {
            return *this > s || *this == s;
        }
        bool operator<=(const string &s) const
        {
            return !(*this > s);
        }
        bool operator<(const string &s) const
        {
            return !(*this >= s);
        }
        bool operator!=(const string &s) const
        {
            return !(*this == s);
        }
    };
    size_t string::npos = -1;
    // << 和 >>
    // 流插入流提取一定是友元吗？不一定！你不用访问私有就不用友元
    std::ostream &operator<<(std::ostream &out, const string &s)
    {
        for (size_t i = 0; i < s.size(); i++)
        {
            out << s[i];
        }
        return out;
    }
    std::istream &operator>>(std::istream &in, string &s)
    {
        s.clear(); // 先记得clear一下
        char ch;
        ch = in.get();
        // 弄一个缓冲区，减少扩容到次数
        const size_t N = 32;
        char buff[N];
        size_t i = 0;
        while (ch != ' ' && ch != '\n')
        {
            buff[i++] = ch;
            if (i == N - 1)
            {
                buff[i] = '\0';
                s += buff; // buff就相当于一个缓冲区
                i = 0;     // 清空buff
            }
            ch = in.get();
        }
        buff[i] = '\0';
        s += buff;
        return in;
    }
} // namespace yufc

#endif