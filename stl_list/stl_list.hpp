

#ifndef __YUFC_STL_LIST__
#define __YUFC_STL_LIST__

#include <cassert>
#include <initializer_list>
#include <boost/mpl/iterator_tags.hpp>

namespace yufc
{
    template <class T>
    struct __list_node
    {
    public:
        T __data;
        __list_node<T> *__next;
        __list_node<T> *__prev;

    public:
        __list_node(const T &x = T()) // 这里给一个全缺省
            : __data(x), __next(nullptr), __prev(nullptr)
        {
        }
    };

    // 迭代器（重要）
    /*
        typedef __list_iterator<T, T&, T*> iterator;
        typedef __list_iterator<T, const T&, const T*> const_iterator;
    */
    template <class T, class Ref, class Ptr>
    struct __list_iterator
    {
    public:
        // stl对迭代器类型的检查，加了这个才能用stl::find那些，不用管为什么
        // 失败了 g++ 和 vsstudio 好像不一样
        typedef boost::mpl::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef ptrdiff_t difference_type;
    public:
        typedef __list_node<T> Node;
        Node *__node;

    public:
        __list_iterator(Node *node)
            : __node(node) {}
        // 需要写析构函数吗？
    public:
        // 控制迭代器的核心行为
        bool operator!=(const __list_iterator<T, reference, pointer> &it) const
        {
            return __node != it.__node;
        }
        bool operator==(const __list_iterator<T, reference, pointer> &it) const
        {
            return __node == it.__node;
        }

    public:
        reference operator*()
        {
            // *重载返回的是那个数字，也就是T&类型(可读可写)
            return __node->__data;
        }
        pointer &operator->()
        {
            return &(operator*());
        }

    public:
        __list_iterator<T, reference, pointer> operator++()
        {
            // 注意，这个是前置++
            // ++ 返回的还是一个迭代器
            __node = __node->__next;
            return *this;
        }
        __list_iterator<T, reference, pointer> operator++(int)
        {
            __list_iterator<T, reference, pointer> tmp(*this);
            __node = __node->__next;
            return tmp;
        }
        __list_iterator<T, reference, pointer> operator--()
        {
            __node = __node->__prev;
            return *this;
        }
        __list_iterator<T, reference, pointer> operator--(int)
        {
            __list_iterator<T, reference, pointer> tmp(*this);
            __node = __node->__prev;
            return tmp;
        }
    };

    template <class T>
    class list
    {
    private:
        typedef __list_node<T> Node;
        Node *__head;

    public:
        typedef __list_iterator<T, T &, T *> iterator;                   // 定义迭代器！
        typedef __list_iterator<T, const T &, const T *> const_iterator; // 定义const迭代器
        iterator begin() { return iterator(__head->__next); }            // 用__head->__next构造__list_node就是迭代器的begin
        iterator end() { return iterator(__head); }                      // end就是head自己
        const_iterator begin() const { return const_iterator(__head->__next); }
        const_iterator end() const { return const_iterator(__head); }

    public:
        list()
        {
            __head = new Node;
            __head->__next = __head;
            __head->__prev = __head;
        }
        list(const std::initializer_list<T> &init_lst)
        {
            // 初始化
            __head = new Node;
            __head->__next = __head;
            __head->__prev = __head;
            for (const auto &e : init_lst)
            {
                push_back(e);
            }
        }

    public:
        void push_back(const T &x)
        {
#if 0
            Node *tail = __head->__prev; // 头节点的前一个节点就是tail
            Node *new_node = new Node(x);
            // 链接new_node
            tail->__next = new_node;
            new_node->__prev = tail;
            new_node->__next = __head;
            __head->__prev = new_node;
#endif
            insert(end(), x);
        }
        void push_front(const T &x)
        {
            insert(begin(), x);
        }
        void pop_back()
        {
            erase(--end());
        }
        void pop_front()
        {
            erase(begin());
        }
        iterator insert(iterator pos, const T &x)
        {
            Node *cur = pos.__node;
            Node *prev = cur->__prev;
            Node *new_node = new Node(x);
            // 链接一下即可
            prev->__next = new_node;
            new_node->__prev = prev;
            new_node->__next = cur;
            cur->__prev = new_node;
            return iterator(new_node);
        }
        iterator erase(iterator pos)
        {
            assert(pos != end());
            Node *cur = pos.__node;
            Node *prev = cur->__prev;
            Node *next = cur->__next;
            // 链接
            prev->__next = next;
            next->__prev = prev;
            delete cur;
            return iterator(next); // 返回删除位置的下一个位置的迭代器
        }
    };
} // namespace yufc

#endif