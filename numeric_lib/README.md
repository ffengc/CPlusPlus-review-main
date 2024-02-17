# C++ `<numeric>` 头文件的学习

## 参考网站

- **[cplusplus.com](https://legacy.cplusplus.com/reference/numeric/)**

我针对这个文档链接里面的顺序进行了这个库的功能学习，并自己进行了一些demo的编写，都总结在下面了。

**文中部分文字来自于cplusplus.com**

标头`<numeric>`定义了一组函数，用于对数值序列执行某些操作。

我下面所有源代码，在仓库里都能找到，**仓库地址：[CPlusPlus-review-main/tree/master/numeric_lib](https://github.com/Yufccode/CPlusPlus-review-main/tree/master/numeric_lib)**


## `accumulate`

```cpp
template <class InputIterator, class T>
   T accumulate (InputIterator first, InputIterator last, T init);
template <class InputIterator, class T, class BinaryOperation>
   T accumulate (InputIterator first, InputIterator last, T init,
                 BinaryOperation binary_op);
```

返回将`[first，last)`范围内的所有值累加到init的结果。这个也是很好理解的。

例子：
```cpp
std::string my_strcat(const std::string& s1, const std::string& s2)
{
    return s1 + s2;
}
void test1()
{
    // accumulate
    std::vector<int> arr = {1, 2, 3, 4, 5};
    int res = std::accumulate(arr.begin(), arr.end(), 0); // 从0开始累加
    std::cout << res << std::endl;
    std::vector<std::string> str_arr = {"aa", "bb", "cc"};
    std::string init = "";
    auto res2 = std::accumulate(str_arr.begin(), str_arr.end(), init, my_strcat);
    std::cout << res2 << std::endl;
}
```

输出：
```
15
aabbcc
```

## `adjacent_difference`

```cpp
template <class InputIterator, class OutputIterator>
   OutputIterator adjacent_difference (InputIterator first, InputIterator last,
                                       OutputIterator result);	
template <class InputIterator, class OutputIterator, class BinaryOperation>
   OutputIterator adjacent_difference ( InputIterator first, InputIterator last,
                                        OutputIterator result, BinaryOperation binary_op );
```

这个函数就是找序列中元素之间的差值，可以这样理解：

x可以代表输入的序列，y可以代表输出的序列

```
y0 = x0
y1 = x1 - x0
y2 = x2 - x1
y3 = x3 - x2
y4 = x4 - x3
... ... ...
```

例子：

```cpp
void test2()
{
    // adjacent_difference
    std::vector<int> arr = {0, 2, 3, 4, 5};
    std::vector<int> res(arr.size());
    std::adjacent_difference(arr.begin(), arr.end(), res.begin());
    print(res);
}
```
输出：`0 2 1 1 1`

## `inner_product`

```cpp
template <class InputIterator1, class InputIterator2, class T>
   T inner_product (InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, T init);
template <class InputIterator1, class InputIterator2, class T,
          class BinaryOperation1, class BinaryOperation2>
   T inner_product (InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, T init,
                    BinaryOperation1 binary_op1,
                    BinaryOperation2 binary_op2);
```

这个函数是对两个序列进行操作。先对两个序列对应下标的元素，进行binary_op2运算，然后对运算的结果从init开始进行binary_op1运算。返回最后的结果。默认的binary_op2是积运算，binary_op1是和运算。因此默认的情况就是对两个序列求内积（对应元素相乘后相加）


例子：
```cpp
void test3()
{
    // inner_product
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2 = {1, 2, 3, 4, 5};
    std::cout << std::inner_product(arr1.begin(), arr1.end(), arr2.begin(), 0) << std::endl;
}
```
输出：`55`

## `partial_sum`

```cpp
template <class InputIterator, class OutputIterator>
   OutputIterator partial_sum (InputIterator first, InputIterator last,
                               OutputIterator result);
template <class InputIterator, class OutputIterator, class BinaryOperation>
   OutputIterator partial_sum (InputIterator first, InputIterator last,
                               OutputIterator result, BinaryOperation binary_op);
```

求序列的前缀和。这个很好理解，看个例子就可以了。

例子：
```cpp
std::string my_strcat2(const std::string &s1, const std::string &s2)
{
    return s1 + s1 + s2 + s2;
}
void test4()
{
    // partial_sum
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> res1(arr1.size());
    std::partial_sum(arr1.begin(), arr1.end(), res1.begin());
    print(res1);
    std::vector<std::string> arr2 = {"a", "b", "c"};
    std::vector<std::string> res2(arr1.size());
    std::partial_sum(arr2.begin(), arr2.end(), res2.begin(), my_strcat2);
    print(res2);
}
```
输出：
```
1 3 6 10 15 
a aabb aabbaabbcc 
```

## `iota`

```cpp
template <class ForwardIterator, class T>
  void iota (ForwardIterator first, ForwardIterator last, T val);
```

给序列赋予一系列从val开始的递增元素

```cpp
void test5()
{
    std::vector<int> arr1(5);
    std::iota(arr1.begin(), arr1.end(), 1);
    print(arr1);
}
```
输出：`1 2 3 4 5`