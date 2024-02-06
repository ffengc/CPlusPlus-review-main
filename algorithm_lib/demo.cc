

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <list>

/* 修改序列操作 */

template <class container_type>
void print(container_type con)
{
    auto first = con.begin();
    auto last = con.end();
    while (first != last)
        std::cout << *first++ << " ";
    std::cout << "\n";
}

void test1()
{
    // copy
    std::list<int> lst1 = {1, 2, 3, 4, 5};
    std::vector<int> arr(lst1.size(), 0); // 要提前扩容，不然就会段错误
    std::copy(lst1.begin(), lst1.end(), arr.begin());
    print(arr);
    // copy_n
    std::vector<int> arr2(4, 0);
    std::copy_n(lst1.begin(), 3, arr2.begin() + 1); // 拷贝到arr2的第二个位置去
    print(arr2);
    // copy_if
    std::vector<int> arr3(5, 0);
    std::copy_if(lst1.begin(), lst1.end(), arr3.begin(), [](int i)
                 { return i <= 3; });
    print(arr3);
    // copy_backward
    std::list<int> lst2 = {1, 2, 3};
    std::vector<int> arr4(lst2.size() + 1, 0);
    std::copy_backward(lst2.begin(), lst2.end(), arr4.end());
    print(arr4); // 0 1 2 3

}

int main()
{
    test1();
    return 0;
}