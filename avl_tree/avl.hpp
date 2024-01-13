
#ifndef __YUFC_AVL_TREE__
#define __YUFC_AVL_TREE__

#include <iostream>
#include <cassert>



template <class K, class V>
struct AVLTreeNode
{
    AVLTreeNode<K, V> *__left;
    AVLTreeNode<K, V> *__right;
    AVLTreeNode<K, V> *__parent;
    std::pair<K, V> __kv; // 数据
    int __bf;             // 平衡因子
    AVLTreeNode(const std::pair<K, V> &kv)
        : __left(nullptr), __right(nullptr), __parent(nullptr), __kv(kv), __bf(0) {}
};

template <class K, class V>
struct AVL
{
    typedef AVLTreeNode<K, V> Node;

private:
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
        // 还要处理一下平衡因子
        subR->__bf = parent->__bf = 0;
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
        subL->__bf = parent->__bf = 0; // 更新平衡因子
    }
    void __rotate_left_right(Node *parent)
    {
        Node *subL = parent->__left;
        Node *subLR = subL->__right;
        int lr_bf = subLR->__bf; // 记录一下平衡因子
        // 旋转过程是一样的，无论是在哪里插入，只要是触发左右双旋
        __rotate_left(parent->__left);
        __rotate_right(parent);
        // 怎么看平衡因子的三种情况？
        // 看parent->__left->__right的平衡因子就行了！所以前面先记录一下

        subLR->__bf = 0; // 这个无论是哪种情况都是0
        if (lr_bf == 1)
        {
            parent->__bf = 0;
            subL->__bf = -1;
        }
        else if (lr_bf == -1)
        {
            parent->__bf = 1;
            subL->__bf = 0;
        }
        else if (lr_bf == 0)
        {
            parent->__bf = 0;
            subL->__bf = 0;
        }
        else
            assert(false);
    }
    void __rotate_right_left(Node *parent)
    {
        Node *subR = parent->__right;
        Node *subRL = subR->__left;

        int rl_bf = subRL->__bf; // 记录一下平衡因子

        __rotate_right(parent->__right);
        __rotate_left(parent);

        subRL->__bf = 0;
        if (rl_bf == 1)
        {
            subR->__bf = 0;
            parent->__bf = -1;
        }
        else if (rl_bf == -1)
        {
            subR->__bf = 1;
            parent->__bf = 0;
        }
        else if (rl_bf == 0)
        {
            subR->__bf = 0;
            parent->__bf = 0;
        }
        else
            assert(false);
    }

public:
    bool Insert(const std::pair<K, V> &kv)
    {
        if (__root == nullptr)
        {
            __root = new Node(kv);
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
        if (parent->__kv.first < kv.first)
            parent->__right = cur;
        else
            parent->__left = cur;
        cur->__parent = parent;
// 调整平衡因子
#if true
        while (parent)
        {
            // 最多更新到根节点，根的parent是null
            if (cur == parent->__right)
            {
                // 新增节点在parent的右边，parent平衡因子++
                parent->__bf++;
            }
            else
            {
                // 新增的节点在parent的左边，parent平衡因子--
                parent->__bf--;
            }
            if (abs(parent->__bf) == 1)
            {
                // 说明还要继续更新
                parent = parent->__parent;
                cur = cur->__parent;
            }
            else if (abs(parent->__bf) == 0)
                break; // 不用继续向上处理了
            else if (abs(parent->__bf) == 2)
            {
                // 触发旋转
                if (parent->__bf == 2 && cur->__bf == 1)
                    __rotate_left(parent); // 左单旋
                else if (parent->__bf == -2 && cur->__bf == -1)
                    __rotate_right(parent); // 右单旋
                else if (parent->__bf == -2 && cur->__bf == 1)
                    __rotate_left_right(parent); // 左右双旋
                else if (parent->__bf == 2 && cur->__bf == -1)
                    __rotate_right_left(parent); // 右左双旋
                else
                    assert(false);
                break;
            }
            else
                assert(false);
        }
#endif
        return true;
    }

public:
    void InOrder()
    {
        __in_order(__root);
        std::cout << std::endl;
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
};

void test1()
{
    int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVL<int, int> avl_tree1;
    for (auto e : arr)
    {
        avl_tree1.Insert(std::make_pair(e, e));
    }
    avl_tree1.InOrder();
}

#endif