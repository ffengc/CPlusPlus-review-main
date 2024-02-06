

#include "Graph.hpp"

void test1()
{
    // 测试邻接矩阵的表示方法
    yufc_graph_matrix::graph<char, int, INT_MAX, true> g("0123", 4);
    g.add_edge('0', '1', 1);
    g.add_edge('0', '3', 4);
    g.add_edge('1', '3', 2);
    g.add_edge('1', '2', 9);
    g.add_edge('2', '3', 8);
    g.add_edge('2', '1', 5);
    g.add_edge('2', '0', 3);
    g.add_edge('3', '2', 6);
    g.print();
}

int main()
{
    test1();
    return 0;
}