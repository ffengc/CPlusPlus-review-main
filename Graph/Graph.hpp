
#ifndef __YUFC_GRAPH_HPP__
#define __YUFC_GRAPH_HPP__

#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include <iostream>
#include <queue>
#include <assert.h>
#include "union_find_disjoint_set.hpp"

namespace yufc_graph_matrix
{
    template <class vertex_type, class weight_type, weight_type __max_weight = INT_MAX, bool direction = false>
    class graph
    {
    private:
        typedef graph<vertex_type, weight_type, __max_weight, direction> self;
        std::vector<vertex_type> __vertexs;             // 顶点的集合
        std::map<vertex_type, int> __index_map;         // 顶点映射的下标
        std::vector<std::vector<weight_type>> __matrix; // 邻接矩阵
    public:
        // 图的创建
        /*
            三种创建图的方法：
            1. IO输入 -- 不方便测试，oj中更合适
            2. 图结构关系写到文件，读取文件
            3. 手动添加边
        */
        graph() = default;
        graph(const vertex_type *a, size_t n)
        {
            __vertexs.reserve(n);
            for (size_t i = 0; i < n; i++)
            {
                __vertexs.push_back(a[i]); // 每个顶点存进去
                __index_map[a[i]] = i;     // 顶点映射的下标，就是这个顶点是__vertexs中哪一个下标上的
            }
            __matrix.resize(n);
            for (size_t i = 0; i < __matrix.size(); ++i)
            {
                __matrix[i].resize(n, __max_weight);
            }
        }
        size_t get_vertex_index(const vertex_type &v)
        {
            /* 确定顶点的下标 */
            auto it = __index_map.find(v);
            if (it != __index_map.end())
                return it->second;
            else
            {
                throw std::invalid_argument("vertex not exists");
                return -1;
            }
        }
        void add_edge(const vertex_type &src, const vertex_type &dest, const weight_type &weight)
        {
            size_t srci = get_vertex_index(src);
            size_t desti = get_vertex_index(dest);
            __add_edge(srci, desti, weight);
        }
        void __add_edge(size_t srci, size_t dsti, const weight_type &weight)
        {
            // 添加一个版本，用下标来添加的，这个函数一般就给内部使用
            __matrix[srci][dsti] = weight;
            // 如果是无向图
            if (direction == false)
                __matrix[dsti][srci] = weight;
        }

    private:
        void __dfs(size_t srci, std::vector<bool> &visited)
        {
            std::cout << __vertexs[srci] << "[" << srci << "]"
                      << " ";
            visited[srci] = true; // 标记访问过了
            // 找一个srci相邻的，没有访问过的点去往深度遍历
            for (size_t i = 0; i < __vertexs.size(); ++i)
                if (__matrix[srci][i] != __max_weight && visited[i] == false) // 遍历矩阵里面有连接的点就行
                    __dfs(i, visited);
        }

    public:
        // 遍历
        void bfs(const vertex_type &src)
        {
            // 需要给一个起点
            size_t srci = get_vertex_index(src); // 找到起点的下标
            std::queue<int> q;
            std::vector<bool> visited(__vertexs.size(), false); // 所有顶点一开始先标记成false
            q.push(srci);                                       // 起点入队列
            visited[srci] = true;                               // 标记起点，因为起点已经入队列了
            int levelSize = 1;
            while (!q.empty())
            {
                // 控制一次出一层
                for (size_t i = 0; i < levelSize; i++)
                {
                    // 队列不为空就继续遍历
                    int front = q.front(); // 队头的数据
                    std::cout << __vertexs[front] << "[" << front << "]"
                              << " "; // 访问这个值
                    q.pop();
                    // 把和front相连的顶点入队
                    for (size_t i = 0; i < __vertexs.size(); ++i)
                    {
                        if (__matrix[front][i] != __max_weight && visited[i] == false)
                        {
                            q.push(i);         // 和当前顶点相连的节点
                            visited[i] = true; // 入队列的，标记一下
                        }
                    }
                }
                std::cout << std::endl; // 出完每一层才去换行
                levelSize = q.size();   // 此时levelSize就是下一层个数，就是现在队列的元素个数，因为我们已经把当前层出完了，剩下的都是下一层的
            }
            std::cout << "bfs done!" << std::endl;
        }
        void dfs(const vertex_type &src)
        {
            size_t srci = get_vertex_index(src);
            std::vector<bool> visited(__vertexs.size(), false);
            __dfs(srci, visited);
            std::cout << std::endl
                      << "dfs done" << std::endl;
        }

    public:
        // 因为我们是用矩阵存边的，不好操作，所以我们定制一个边的类型
        struct __edge
        {
            size_t __srci;
            size_t __dsti;
            weight_type __weight;
            // __edge() = default;
            __edge(size_t srci, size_t dsti, const weight_type &w)
                : __srci(srci), __dsti(dsti), __weight(w) {}
            bool operator>(const __edge &e) const { return this->__weight > e.__weight; }
        };
        // 最小生成树
        weight_type Kruskal(self &minTree)
        {
            // 要先初始化最小生成树
            size_t n = __vertexs.size();
            minTree.__vertexs = this->__vertexs;
            minTree.__index_map = this->__index_map;
            minTree.__matrix.resize(n);
            for (size_t i = 0; i < n; i++)
                minTree.__matrix[i].resize(n, __max_weight);
            assert(direction == false); // 只能无向图
            // 如果有最小生成树，就返回到minTree里面，如果没有，就返回一个默认的weight_type
            // 然后比较边，优先队列要重载一个比较才行
            std::priority_queue<__edge, std::vector<__edge>, std::greater<__edge>> minq;
            for (size_t i = 0; i < n; i++)
                for (size_t j = 0; j < n; j++)
                    if (i < j && __matrix[i][j] != __max_weight) // 表示有这条边，那就把这条边加入到优先队列中, i<j 可以保证无向图不会重复添加边
                        minq.push(__edge(i, j, __matrix[i][j]));
            // 找到最小的边，依次添加
            int size = 0;                             // 选出n-1条边就行了
            weight_type total_weight = weight_type(); // 总的权值
            union_find_disjoint_set<int> ufs(n);      // 这里不能用size_t
            while (!minq.empty())
            {
                __edge min = minq.top(); // 选出一条边
                minq.pop();
                if (ufs.InSet(min.__srci, min.__dsti))
                    continue;                                             // 如果这个边的两个顶点在一个集合里面，直接跳过本轮
                minTree.__add_edge(min.__srci, min.__dsti, min.__weight); // 添加边就行了
                ufs.Union(min.__srci, min.__dsti);
                size++;
                total_weight += min.__weight;
            }
            if (size == n - 1)
                return total_weight;
            else
                return weight_type(); // 如果找不到，就返回一个缺省值
        }
        weight_type Prim(self &minTree, const vertex_type &src)
        {
            // 同样先初始化
            size_t n = __vertexs.size();
            minTree.__vertexs = this->__vertexs;
            minTree.__index_map = this->__index_map;
            minTree.__matrix.resize(n);
            for (size_t i = 0; i < n; i++)
                minTree.__matrix[i].resize(n, __max_weight);
            // prim算法需要一个原点
            size_t srci = get_vertex_index(src);
            std::set<int> X; // 加入了集合的点集合
            std::set<int> Y; // 还没加入集合的点的集合
            X.insert(srci);
            for (size_t i = 0; i < n; ++i)
                if (i != srci)
                    Y.insert(i);
            // 找X->Y中连接的边中选择最小的边
            // 如果我们用优先队列的话，就有可能构成环
            // 所以我们额外添加一步探环
            std::priority_queue<__edge, std::vector<__edge>, std::greater<__edge>> minq;
            
        }

    public:
        void print()
        {
            // 把顶点打印出来
            for (size_t i = 0; i < __vertexs.size(); i++)
                std::cout << "[" << i << "]"
                          << "->" << __vertexs[i] << std::endl;
            std::cout << std::endl;
            // 打印一下矩阵
            // 先打印一下下标
            std::cout << "  ";
            for (size_t i = 0; i < __vertexs.size(); ++i)
                std::cout << i << " ";
            std::cout << std::endl;
            for (size_t i = 0; i < __matrix.size(); ++i)
            {
                // 先打印一下下标
                std::cout << i << " ";
                for (size_t j = 0; j < __matrix[i].size(); ++j)
                    if (__matrix[i][j] == __max_weight)
                        std::cout << "* ";
                    else
                        std::cout << __matrix[i][j] << " ";
                std::cout << std::endl;
            }
        }
    };
}

namespace yufc_graph_link_table
{
    template <class weight_type>
    struct edge
    {
        int __dest_idx;            // 目标点的下标
        weight_type __weight;      // 权值
        edge<weight_type> *__next; // 链接指针
        edge(int desti, const weight_type &weight)
            : __dest_idx(desti), __weight(weight), __next(nullptr) {}
    };
    template <class vertex_type, class weight_type, bool direction = false>
    class graph
    {
    private:
        typedef edge<weight_type> Edge;
        std::vector<vertex_type> __vertexs;     // 顶点的集合
        std::map<vertex_type, int> __index_map; // 顶点映射的下标
        std::vector<Edge *> __table;            // 下面挂边
    public:
        graph(const vertex_type *a, size_t n)
        {
            __vertexs.reserve(n);
            for (size_t i = 0; i < n; i++)
            {
                __vertexs.push_back(a[i]); // 每个顶点存进去
                __index_map[a[i]] = i;     // 顶点映射的下标，就是这个顶点是__vertexs中哪一个下标上的
            }
            // 初始化邻接表
            __table.resize(n, nullptr);
        }
        size_t get_vertex_index(const vertex_type &v)
        {
            /* 确定顶点的下标 */
            auto it = __index_map.find(v);
            if (it != __index_map.end())
                return it->second;
            else
            {
                throw std::invalid_argument("vertex not exists");
                return -1;
            }
        }
        void add_edge(const vertex_type &src, const vertex_type &dest, const weight_type &weight)
        {
            size_t srci = get_vertex_index(src);
            size_t desti = get_vertex_index(dest);
            Edge *eg = new Edge(desti, weight);
            // 头插
            eg->__next = __table[srci];
            __table[srci] = eg;
            if (direction == false)
            {
                // 无向图反过来还要弄一下才行
                Edge *eg = new Edge(srci, weight);
                eg->__next = __table[desti];
                __table[desti] = eg;
            }
        }

    public:
        // 遍历
        void bfs(const vertex_type &src)
        {
        }

    public:
        void print(bool is_print_direction = false) // 默认不打印权值
        {
            // 把顶点打印出来
            for (size_t i = 0; i < __vertexs.size(); i++)
                std::cout << "[" << i << "]"
                          << "->" << __vertexs[i] << std::endl;
            std::cout << std::endl;
            //
            for (size_t i = 0; i < __table.size(); ++i)
            {
                std::cout << __vertexs[i] << "[" << i << "]->";
                Edge *cur = __table[i]; // 遍历一下单链表而已
                while (cur)
                {
                    if (is_print_direction == true)
                        std::cout << cur->__weight << "->" << __vertexs[cur->__dest_idx] << "[" << cur->__dest_idx << "]->";
                    else
                        std::cout << __vertexs[cur->__dest_idx] << "[" << cur->__dest_idx << "]->";
                    cur = cur->__next;
                }
                std::cout << "nullptr" << std::endl;
            }
        }
    };
}

#endif