
#include <iostream>
#include <stddef.h>
#include <vector>
#include <time.h>
#include <assert.h>
#include <chrono>
#include <random>
#include <initializer_list>

#define __DEBUG

#ifdef __DEBUG
#include <unordered_map>
#endif

namespace yufc
{
    template <class key_type, class value_type>
    struct __skip_list_node
    {
    public:
        std::pair<key_type, value_type> __kv;
        std::vector<__skip_list_node *> __next_vector;

    public:
        __skip_list_node(const std::pair<key_type, value_type> &kv, int level)
            : __kv(kv), __next_vector(level, nullptr) {}
    };

    template <class key_type, class value_type, class pair_type> /* 有可能是const的也有可能不是const的 */
    struct __skip_list_iterator
    {
    public:
        typedef __skip_list_node<key_type, value_type> Node;
        typedef __skip_list_iterator<key_type, value_type, pair_type> self;
        Node *__node;
        __skip_list_iterator(Node *node)
            : __node(node) {}
        // key肯定是不能改的，一定要const
        // value可以改, 假设是int, 那么这个value_type可能是int, 也可能是const int
    public:
        bool operator!=(const self &it) const { return __node != it.__node; }
        bool operator==(const self &it) const { return __node == it.__node; }

    public:
        pair_type &operator*() { return __node->__kv; }
        pair_type *operator->() { return &(operator*()); }
        // 只有单向迭代器
        self operator++()
        {
            // 注意，这个是前置++
            // ++ 返回的还是一个迭代器
            __node = __node->__next_vector[0];
            return *this;
        }
        self operator++(int)
        {
            self tmp(*this);
            __node = __node->__next_vector[0];
            return tmp;
        }
    };

    template <class key_type, class value_type>
    class skip_list
    {
    private:
        typedef __skip_list_node<key_type, value_type> Node;
        Node *__head;
        size_t __max_level = 32; // 就按照redis的给吧，给个32，概率给个0.25
        double __p = 0.25;
        size_t __size = 0;

    public:
        typedef __skip_list_iterator<key_type, value_type, std::pair<key_type, value_type>> iterator; // key要带上const，因为key是不能改的！
        typedef __skip_list_iterator<key_type, value_type, const std::pair<key_type, value_type>> const_iterator;
        iterator begin() { return iterator(__head->__next_vector[0]); }
        iterator end() { return iterator(nullptr); }
        const_iterator begin() const { return const_iterator(__head->__next_vector[0]); }
        const_iterator end() const { return const_iterator(nullptr); }

    private:
        // 获取随机层数
        int __random_level()
        {
            static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            static std::default_random_engine generator(seed);
            std::uniform_real_distribution<double> distribution(0.0, 1.0);
            size_t level = 1;
            while (distribution(generator) <= __p && level < __max_level)
                ++level;
            return level;
        }

    public:
        size_t size() const { return __size; }
        void clear()
        {
            Node *cur = __head->__next_vector[0]; // 指向第一个节点
            while (cur)
            {
                Node *node_to_free = cur;
                cur = cur->__next_vector[0];
                delete node_to_free;
            }
            // 这几步记得弄一下
            __size = 0;
            __head->__next_vector.resize(1);
            __head->__next_vector[0] = nullptr;
        }
        bool empty() const { return __head->__next_vector[0] == nullptr; }

    private:
        std::vector<Node *> __find_prev_vector(key_type key)
        {
            Node *cur = __head;
            int level = __head->__next_vector.size() - 1;
            std::vector<Node *> prev_vector(level + 1, __head);
            while (level >= 0)
            {
                if (cur->__next_vector[level] && cur->__next_vector[level]->__kv.first < key)
                    cur = cur->__next_vector[level];
                else if (cur->__next_vector[level] == nullptr || cur->__next_vector[level]->__kv.first >= key)
                {
                    // 不仅要向下走，还要更新prev_vector
                    prev_vector[level] = cur;
                    --level;
                }
            }
            return prev_vector;
        }
        void __empty_initialize() { __head = new Node({-1, -1}, 1); }
        template <class iterator_type>
        void __iterator_initialize(iterator_type first, iterator_type last)
        {
            while (first != last)
                insert(*first++);
        }
    public:
        skip_list() { __empty_initialize(); }
        ~skip_list()
        {
            clear();
            delete __head;
        }
        template <class InputIterator>
        skip_list(InputIterator first, InputIterator last)
        {
            __empty_initialize();
            __iterator_initialize(first, last);
        }
        skip_list(const std::initializer_list<std::pair<key_type, value_type>> &init_list)
        {
            __empty_initialize();
            __iterator_initialize(init_list.begin(), init_list.end());
        }
        skip_list(const skip_list<key_type, value_type> &lst)
        {
            __empty_initialize();
            __iterator_initialize(lst.begin(), lst.end());
        }
        skip_list<key_type, value_type> &operator=(const skip_list<key_type, value_type> &lst)
        {
            clear();
            __iterator_initialize(lst.begin(), lst.end());
            return *this;
        }

        std::pair<value_type, bool> find(key_type target)
        {
            Node *cur = __head;
            int level = __head->__next_vector.size() - 1; // 这个就是最高层数
            /* 这个level不要用 size_t 因为有可能减到 -1 去 */
            while (level >= 0)
            {
                // 下一个位置存在 && target比下一个位置要大，继续跳，向右走
                if (cur->__next_vector[level] && cur->__next_vector[level]->__kv.first < target)
                    cur = cur->__next_vector[level]; // 向右走
                // 下一个位置不存在 && target比下一个位置要小，不跳了，向下走
                else if (cur->__next_vector[level] == nullptr || cur->__next_vector[level]->__kv.first > target)
                    --level; // 向下走
                else
                    return {cur->__next_vector[level]->__kv.second, true};
            }
            return {value_type(), false};
        }
        bool insert(std::pair<key_type, value_type> kv)
        {
            __size++; // 计数器++
            /*
                关键是：要找到插入位置的每一层的前面的一系列指针
                但是注意，这一系列指针不一定在同一个vector里面
                因为层数是不知道的，所以这个prev_vector的高度一定先初始化为最高（当前最高，不是只maxLevel）
                具体解释可以看看readme，里面有图，我把prev_vector圈起来了
            */
            std::vector<Node *> prev_vector = __find_prev_vector(kv.first);
            if (prev_vector[0]->__next_vector[0] && prev_vector[0]->__next_vector[0]->__kv.first == kv.first)
                return false; // 说明已经有这个key了
            int n = __random_level();
            Node *newnode = new Node(kv, n);
            // 如果 n 比 head 高，head层数不够怎么办
            if (n > __head->__next_vector.size())
            {
                __head->__next_vector.resize(n, nullptr); // 如果n比head高才升高
                prev_vector.resize(n, __head);
            }
            // 连接前后节点
            for (size_t i = 0; i < n; i++)
            {
                newnode->__next_vector[i] = prev_vector[i]->__next_vector[i];
                prev_vector[i]->__next_vector[i] = newnode;
            }
            return true;
        }
        bool erase(key_type key)
        {
            // 同样也是找到每一层的前一个
            // 删掉之后链接起来就可以了，不用考虑别人
            std::vector<Node *> prev_vector = __find_prev_vector(key);
            // 看最下面的这一层就行了，如果最下面的prev_vector指向空，说明找到最右边也没找到
            // 如果最下面这一层的下一个的val不是对应的值，也不对了，说明找不到了
            // 而且最下面这一层的下一个的val一定是大于num的，如果找不到的话
            if (prev_vector[0]->__next_vector[0] == nullptr || prev_vector[0]->__next_vector[0]->__kv.first != key)
                return false;
            Node *del = prev_vector[0]->__next_vector[0]; // 最下面这一层的下一个
            for (size_t i = 0; i < del->__next_vector.size(); i++)
                prev_vector[i]->__next_vector[i] = del->__next_vector[i];
            // 这样就可以了
            delete del;
            // 检查一下是否删除的是最高的节点
            /* 如果头节点的最高层指向的是空，那么这一层就可以删掉了 */
            while (__head->__next_vector.size() > 1 && __head->__next_vector[__head->__next_vector.size() - 1] == nullptr)
                __head->__next_vector.pop_back();
            --__size;
            return true;
        }
    };
}