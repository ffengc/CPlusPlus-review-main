

#ifndef __YUFC_UNION_DISJOINT_SET_HPP__
#define __YUFC_UNION_DISJOINT_SET_HPP__

#include <vector>

template <class T>
class union_find_disjoint_set
{
private:
    std::vector<T> __ufs; // 通过编号找人
public:
    union_find_disjoint_set(size_t n)
        : __ufs(n, -1) {} // 先初始化成-1
    void Union(int x1, int x2)
    {
        int root1 = FindRoot(x1);
        int root2 = FindRoot(x2);
        if (root1 == root2) // 如果在一个集合就没必要合并了
            return;
#if false
        if (root1 > root2)
            std::swap(root1, root2); // 统一让下标小的根去合并大的根，其实这个是没有要求的
#endif
        // 稍微优化一下，数据量小的往数据量大的集合合并
        if (abs(__ufs[root1]) < abs(__ufs[root2]))
            std::swap(root1, root2);
        __ufs[root1] += __ufs[root2];
        __ufs[root2] = root1;
    }
    int FindRoot(int x)
    {
        int root = x;
        while (__ufs[root] >= 0)
            root = __ufs[root];
        // 路径压缩
        while (__ufs[x] >= 0)
        {
            int parent = __ufs[x];
            __ufs[x] = root;
            x = parent;
        }
        return root;
    }
    bool InSet(int x1, int x2) // 判断是否在同一个集合
    {
        return FindRoot(x1) == FindRoot(x2);
    }
    size_t SetSize()
    {
        size_t cnt = 0;
        for (const auto &e : __ufs)
            if (e < 0)
                ++size;
        return size;
    }
};
#endif