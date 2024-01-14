

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

template <class K, class V>
struct rb_tree_node
{
    /* data */
    rb_tree_node<K, V> *__left;
    rb_tree_node<K, V> *__right;
    rb_tree_node<K, V> *__parent;
    std::pair<K, V> __kv;
    Color __node_color;
    rb_tree_node(const std::pair<K, V> &kv)
        : __left(nullptr), __right(nullptr), __parent(nullptr), __kv(kv) {}
};

template <class K, class V>
struct rb_tree
{
private:
    typedef rb_tree_node<K, V> Node;
    Node *__root = nullptr;

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

private:
    void __in_order(Node *root)
    {
        if (root == nullptr)
            return;
        __in_order(root->__left);
        std::cout << root->__kv.first << ":" << root->__kv.second << std::endl;
        __in_order(root->__right);
    }
    void __prev_check(Node *root, int black_number, std::set<int> &black_number_set)
    {
        if (root == nullptr)
        {
            // std::cout << "black_number: " << black_number << std::endl;
            black_number_set.insert(black_number);
            return;
        }
        if (root->__node_color == BLACK)
            ++black_number;
        __prev_check(root->__left, black_number, black_number_set);
        __prev_check(root->__right, black_number, black_number_set);
    }

public:
    void InOrder()
    {
        __in_order(__root);
    }
    bool CheckValidation()
    {
        // 测试红黑树是否合法
        // 按照红黑树的规则去检查一下颜色是否合法
        if (__root == nullptr)
            return true;
        if (__root->__node_color == RED)
        {
            std::cerr << "[红黑树非法]: 根节点不是黑色" << std::endl;
            return false;
        }
        std::set<int> black_number_set;
        __prev_check(__root, 0, black_number_set);
        /*
            这里本来想用一个set看看是不是都是一个数字了，
            但是想到set底层就是红黑树，红黑树还用set就很抽象
            但是这个是合法性检验，用一下吧那就
            其实用标志也是可以的，很简单，就先算一条当做参考值，然后看其他是不是和这条一样就行
        */
        if (black_number_set.size() == 1)
            return true;
        std::cerr << "[红黑树非法]: 简单路径上黑色节点数出现不同" << std::endl;
        return false;
    }

public:
    bool Insert(const std::pair<K, V> &kv)
    {
        if (__root == nullptr)
        {
            __root = new Node(kv);
            __root->__node_color = BLACK; // 根节点一定是黑的
            return true;
        }
        Node *parent = nullptr;
        Node *cur = __root;
        // 插入
        while (cur)
        {
            if (cur->__kv.first < kv.first)
            {
                parent = cur;
                cur = cur->__right;
            }
            else if (cur->__kv.first > kv.first)
            {
                parent = cur;
                cur = cur->__left;
            }
            else
                return false;
        }
        cur = new Node(kv);
        cur->__node_color = RED;
        if (parent->__kv.first < kv.first)
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
        return true;
    }
};

#endif