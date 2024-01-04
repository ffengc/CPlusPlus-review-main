

#ifndef __YUFC_STL_LIST__
#define __YUFC_STL_LIST__

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
    template <class T>
    struct __list_iterator
    {
    public:
        typedef __list_node<T> Node;
        Node *__node;

    public:
        __list_iterator(Node *node)
            : __node(node) {}

    public:
        // 控制迭代器的核心行为
        bool operator!=(const __list_iterator<T> &it) const
        {
            return __node != it.__node;
        }
        T &operator*()
        {
            // *重载返回的是那个数字，也就是T&类型(可读可写)
            return __node->__data;
        }
        __list_iterator<T> &operator++()
        {
            // 注意，这个是前置++
            // ++ 返回的还是一个迭代器
            __node = __node->__next;
            return *this;
        }
    };

    template <class T>
    class list
    {
    private:
        typedef __list_node<T> Node;
        Node *__head;

    public:
        typedef __list_iterator<T> iterator;                  // 定义迭代器！
        iterator begin() { return iterator(__head->__next); } // 用__head->__next构造__list_node就是迭代器的beginå
        iterator end() { return iterator(__head); }           // end就是head自己
    public:
        list()
        {
            __head = new Node;
            __head->__next = __head;
            __head->__prev = __head;
        }
        void push_back(const T &x)
        {
            Node *tail = __head->__prev; // 头节点的前一个节点就是tail
            Node *new_node = new Node(x);
            // 链接new_node
            tail->__next = new_node;
            new_node->__prev = tail;
            new_node->__next = __head;
            __head->__prev = new_node;
        }
    };
} // namespace yufc

#endif