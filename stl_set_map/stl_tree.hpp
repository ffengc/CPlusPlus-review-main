

#ifndef __YUFC_RED_BALCK_TREE__
#define __YUFC_RED_BALCK_TREE__

#include <cassert>
#include <iostream>
#include <set>

enum Color
{
    RED,
    BLACK
};

template <class value_type>
struct rb_tree_node
{
    /* data */
    rb_tree_node<value_type> *__left;
    rb_tree_node<value_type> *__right;
    rb_tree_node<value_type> *__parent;
    value_type __data;
    Color __node_color;
    rb_tree_node(const value_type &data)
        : __left(nullptr), __right(nullptr), __parent(nullptr), __data(data) {}
};

template <class value_type, class Ref, class Ptr>
struct __rb_tree_iterator
{
    typedef rb_tree_node<value_type> Node;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<value_type, Ref, Ptr> self;
    Node *__node;
    __rb_tree_iterator(Node *node)
        : __node(node) {}
    reference operator*()
    {
        return __node->__data;
    }
    pointer operator->()
    {
        return &__node->__data;
    }
    bool operator!=(const self &s) const
    {
        return __node != s.__node;
    }
    bool operator==(const self &s) const
    {
        return __node == s.__node;
    }
    void __increment()
    {
        // 如果右子树不为空，++就是右子树的最左节点
        // 如果右子树为空，++就是找祖先，找第一个在自己右上方的第一个祖先
        if (__node->__right)
        {
            // 如果右存在，找到右子树的最左节点
            Node *left = __node->__right;
            while (left->__left)
                left = left->__left;
            __node = left;
        }
        else
        {
            // 如果右子树为空，++就是找祖先，找第一个在自己右上方的第一个祖先
            Node *parent = __node->__parent;
            Node *cur = __node;
            while (parent && cur == parent->__right)
            {
                cur = cur->__parent;
                parent = parent->__parent;
            }
            __node = parent;
            // 记得处理找到根的情况
        }
    }
    void __decrement()
    {
        if (__node->__left)
        {
            // 如果左树不为空，就是左树的最右节点
            Node *right = __node->__left;
            while (right->__right)
            {
                right = right->__right;
            }
            __node = right;
        }
        else
        {
            // 如果左树为空，就找祖先，第一个在左方上的祖先
            Node *parent = __node->__parent;
            Node *cur = __node;
            while (parent && cur == parent->__left)
            {
                cur = cur->__parent;
                parent = parent->__parent;
            }
            __node = parent;
        }
    }
    self operator++(int)
    {
        self tmp = *this;
        __increment();
        return tmp;
    }
    self operator--(int)
    {
        self tmp = *this;
        __decrement();
        return tmp;
    }
    self &operator++()
    {
        __increment();
        return *this;
    }
    self &operator--()
    {
        __decrement();
        return *this;
    }
};

template <class key, class value_type, class key_of_value>
struct rb_tree
{
private:
    typedef rb_tree_node<value_type> Node;
    Node *__root = nullptr;

public:
    // 迭代器
    typedef __rb_tree_iterator<value_type, value_type &, value_type *> iterator;
    iterator begin()
    {
        // 找中序第一个节点（最左节点）
        Node *left = __root;
        while (left && left->__left)
            left = left->__left;
        return iterator(left); // 构造一个迭代器
    }
    iterator end()
    {
        // 用空来当作end即可
        return iterator(nullptr);
    }

private:
    void __rotate_left(Node *parent)
    {
        // 一定要看图，边画边写代码！
        Node *subR = parent->__right;
        Node *subRL = subR->__left;

        parent->__right = subRL;
        if (subRL)
            subRL->__parent = parent;

        Node *ppNode = parent->__parent; // 先记录parent的parent先

        subR->__left = parent;
        parent->__parent = subR;

        // 下面这里很重要，不要忘记了，因为parent上面是还有东西的
        if (__root == parent)
        {
            __root = subR;
            subR->__parent = nullptr;
        }
        else
        {
            if (ppNode->__left == parent)
                ppNode->__left = subR;
            else if (ppNode->__right == parent)
                ppNode->__right = subR;
            subR->__parent = ppNode;
        }
    }
    void __rotate_right(Node *parent)
    {
        Node *subL = parent->__left;
        Node *subLR = subL->__right;

        parent->__left = subLR;
        if (subLR)
            subLR->__parent = parent;

        Node *ppNode = parent->__parent;
        subL->__right = parent;
        parent->__parent = subL;
        if (__root == parent)
        {
            __root = subL;
            subL->__parent = nullptr;
        }
        else
        {
            if (ppNode->__left == parent)
                ppNode->__left = subL;
            else
                ppNode->__right = subL;
            subL->__parent = ppNode;
        }
    }

public:
    std::pair<iterator, bool> Insert(const value_type &data)
    {
        key_of_value kov; // 仿函数
        if (__root == nullptr)
        {
            __root = new Node(data);
            __root->__node_color = BLACK; // 根节点一定是黑的
            return std::make_pair(iterator(__root), true);
        }
        Node *parent = nullptr;
        Node *cur = __root;
        // 插入
        while (cur)
        {
            if (kov(cur->__data) < kov(data))
            {
                parent = cur;
                cur = cur->__right;
            }
            else if (kov(cur->__data) > kov(data))
            {
                parent = cur;
                cur = cur->__left;
            }
            else
                return std::make_pair(iterator(cur), false);
        }
        cur = new Node(data);
        Node *new_node = cur; // 记录一下新增的节点，方便返回
        cur->__node_color = RED;
        if (kov(parent->__data) < kov(data))
            parent->__right = cur;
        else
            parent->__left = cur;
        cur->__parent = parent;
        // 开始处理旋转和变色
        while (parent && parent->__node_color == RED)
        {
            Node *grand_father = parent->__parent;
            assert(grand_father);
            assert(grand_father->__node_color == BLACK);
            /* 如果父亲是祖父的左，叔叔就是祖父的右 */
            if (parent == grand_father->__left)
            {
                Node *uncle = grand_father->__right;
                // 情况1
                if (uncle && uncle->__node_color == RED)
                {
                    // 叔叔存在且叔叔为红 --> 变色就行了，不用旋转
                    /*
                        父亲和叔叔变黑
                        祖父变红
                    */
                    parent->__node_color = uncle->__node_color = BLACK;
                    grand_father->__node_color = RED;
                    // 继续向上处理
                    cur = grand_father;
                    parent = cur->__parent;
                }
                else // 情况2+情况3
                {
                    // 1. uncle不存在 2. uncle存在且为黑
                    if (cur == parent->__left)
                    {
                        // 情况2: 单旋的情况：g,p,cur在一条直线上
                        __rotate_right(grand_father);
                        // 旋转完记得变色
                        // 父亲变黑，祖父一定要变红
                        parent->__node_color = BLACK;
                        grand_father->__node_color = RED;
                    }
                    else
                    {
                        // 情况3: g,p,cur是一条折线
                        __rotate_left(parent);
                        __rotate_right(grand_father);
                        cur->__node_color = BLACK; // 变色这些都是看图就能搞定的了
                        grand_father->__node_color = RED;
                    }
                    break; // 此时这种情况之后，一定要break，只有情况1是要继续向上迭代的
                }
            }
            else if (parent == grand_father->__right)
            {
                Node *uncle = grand_father->__left;
                // 情况1
                if (uncle && uncle->__node_color == RED)
                {
                    parent->__node_color = uncle->__node_color = BLACK;
                    grand_father->__node_color = RED;
                    cur = grand_father;
                    parent = cur->__parent;
                }
                else // 情况2+情况3
                {
                    // 1. uncle不存在 2. uncle存在且为黑
                    if (cur == parent->__right)
                    {
                        // 情况2: 单旋的情况：g,p,cur在一条直线上
                        __rotate_left(grand_father);
                        parent->__node_color = BLACK;
                        grand_father->__node_color = RED;
                    }
                    else
                    {
                        // 情况3: g,p,cur是一条折线
                        __rotate_right(parent);
                        __rotate_left(grand_father);
                        cur->__node_color = BLACK;
                        grand_father->__node_color = RED;
                    }
                    break;
                }
            }
        }
        // 这里要处理，循环结束之后，此时parent是空，也就是cur是根，也就是上一轮的祖父是根
        __root->__node_color = BLACK;
        return std::make_pair(iterator(new_node), false); // 这里不能直接返回cur，因为变色旋转cur可能变了，所以前面先记录一下
    }
};

#endif