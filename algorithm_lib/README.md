# C++ `<algorithm>` 头文件的学习

## 参考网站

- **[cplusplus.com](https://legacy.cplusplus.com/reference/random/)**

我针对这个文档链接里面的顺序进行了这个库的功能学习，并自己进行了一些demo的编写，都总结在下面了。

**文中部分文字来自于cplusplus.com**

标头`<algorithm>`定义了一组函数，这些函数专门设计用于迭代器。
迭代器是可以通过迭代器或指针访问的任何对象序列，例如一些STL容器的数组或实例。不过，请注意，算法直接通过迭代器对值进行操作，不会以任何方式影响任何可能的容器的结构（它永远不会影响容器的大小或存储分配）。

其实这些算法，把迭代器的优势发挥了出来，这就是封装、重载的魅力。

我下面所有源代码，在仓库里都能找到，**仓库地址：[CPlusPlus-review-main/tree/master/algorithm_lib](https://github.com/Yufccode/CPlusPlus-review-main/tree/master/algorithm_lib)**

## 非修改序列操作

### `all_of`

```cpp
template<class InputIterator, class UnaryPredicate>
bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred)
```

如果序列中所有元素都符合pred，则返回true

如：
```cpp
std::vector<int> arr = {1, 2, 3, 4, 5};
std::cout << std::all_of(arr.begin(), arr.end(), [](int i) { return i % 2 == 0; }) << std::endl;
```
如果数组里面元素模2都为0，返回true
输出：
```bash
0
```

### `any_of`

和`all_of`是相反，`all_of`是所有满足pred才返回true，`any_of`就是有其中一个满足，就能返回true了

```cpp
std::vector<int> arr2 = {1, 2, 4, 5};
std::cout << std::any_of(arr2.begin(), arr2.end(), [](int i) { return i % 3 == 0; }) << std::endl;
```
输出：
```bash
0
```

### `none_of`

没有一个满足pred，返回true

```cpp
// none_of
std::vector<int> arr3 = {1, 2, 3, 4, 5};
std::cout << std::none_of(arr3.begin(), arr3.end(), [](int i)
                            { return i < 0; })
            << std::endl;
```
没一个小于0，所以是true
输出：
```bash
1
```

### `for_each`

```cpp
template <class InputIterator, class Function>
Function for_each (InputIterator first, InputIterator last, Function fn);
```

给序列中每一个元素去调用fn

```cpp
void func(int i)
{
    std::cout << "hello world: " << i << std::endl;
}
struct func_class
{
    void operator()(int i)
    {
        std::cout << "hello world: " << i << std::endl;
    }
};
void test2()
{
    std::vector<int> arr = {1, 2, 3};
    std::for_each(arr.begin(), arr.end(), func);
    std::for_each(arr.begin(), arr.end(), func_class());
}
```
这两种形式是一样的，如果是类的话就重载一个()调用就行，如果是函数就直接传过来就行。

这里的输出很简单，就不展示了。

还可以结合bind一起用。

```cpp
void func(int i, int j)
{
    std::cout << "hello world: " << i << ":" << j << std::endl;
}
void test2()
{
    auto bind_func = std::bind(func, 5, std::placeholders::_1);
    std::vector<int> arr = {1, 2, 3};
    std::for_each(arr.begin(), arr.end(), bind_func);
    std::for_each(arr.begin(), arr.end(), func_class());
}
```
输出：
```bash
hello world: 5:1
hello world: 5:2
hello world: 5:3
hello world: 1
hello world: 2
hello world: 3
```


### `find`

这个很常用了。

```cpp
template <class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last, const T& val);
```

第一个等于val的，返回这个位置的迭代器。

**需要要求T带有`operator==`重载。**

```cpp
void test3()
{
    std::vector<std::string> arr = {"aa", "bb", "cc", "dd"};
    auto it = std::find(arr.begin(), arr.end(), "bb");
    std::cout << *it++ << std::endl;
    std::cout << *it << std::endl;
}
```
输出：
```bash
bb
cc
```
这个例子也很简单了，没什么好说的。

### `find_if`

```cpp
template <class InputIterator, class UnaryPredicate>
InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
```

在序列中找到第一个符合pred的元素。

```cpp
// find_if
std::unordered_map<int, std::string> hash_map = {{1, "aa"}, {2, "bb"}, {3, "cc"}};
auto it2 = std::find_if(hash_map.begin(), hash_map.end(), [](const std::pair<int, std::string> p)
                        { return p.second == "bb"; });
std::cout << it2->first << ":" << it2->second << std::endl;
```

输出：
```
2:bb
```

### `find_if_not`

和上面的`find_if`是相反的。`find_if_not`找第一个不符合的。

```cpp
// find_if_not
std::set<int, std::greater<int>> s = {-1, -2, -3, -4, 1, 2, 3, 4};
auto it3 = std::find_if_not(s.begin(), s.end(), [](int i)
                            { return i > 0; });
std::cout << *it3++ << std::endl; // 这个应该是-1
std::cout << *it3 << std::endl;   // 这个应该是-2
// 原本是升序的，我用了greater，所以是降序
```

输出：
```bash
-1
-2
```

### `find_end`

在范围`[first1，last1)`中搜索`[first2，last2)`定义的序列的最后一次出现，并将迭代器返回到其第一个元素，如果未找到出现，则返回last1。在C++11中，如果`[first2，last2)`是空序列，也返回last1。

例子：
```cpp
// find_end
std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6};
std::vector<int> sub_arr = {4, 5, 6};
auto it = std::find_end(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
std::cout << "arr[" << it - arr.begin() << "] = " << *it << std::endl;
```
输出：
```bash
arr[10] = 4
```

### `find_first_of`

Returns an iterator to the first element in the range`[first1,last1)`that matches any of the elements in `[first2,last2)`. If no such element is found, the function returns last1.

其实和`find_end`相反，`find_end`是找最后一次出现，`find_first_of`是找第一次出现。

例子放在一起就很好理解了。

```cpp
void test4()
{
    // find_end
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6};
    std::vector<int> sub_arr = {4, 5, 6};
    auto it = std::find_end(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
    std::cout << "arr[" << it - arr.begin() << "] = " << *it << std::endl;
    // find_first_of
    auto it2 = std::find_first_of(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
    std::cout << "arr[" << it2 - arr.begin() << "] = " << *it2 << std::endl;
}
```
输出结果：
```bash
arr[10] = 4
arr[3] = 4
```

### `adjacent_find`

```cpp
template <class ForwardIterator>
ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last);
template <class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last, BinaryPredicate pred);
```

在范围`[first，last)`中搜索匹配的两个连续元素的第一次出现，并将迭代器返回到这两个元素中的第一个，如果找不到这样的对，则返回到最后last。

```cpp
struct my_pair_cmp
{
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2)
    {
        return p1.first == p2.first;
    }
};
void test5()
{
    // adjacent_find
    std::vector<std::pair<int, int>> arr = {{1, 2}, {2, 2}, {2, 3}, {-1, 2}, {0, 0}, {0, 1}};
    auto it = std::adjacent_find(arr.begin(), arr.end(), my_pair_cmp());
    printf("arr[%d].first = arr[%d].first = %d\n", it - arr.begin(), it - arr.begin() + 1, it->first);
}
```
输出：
```bash
arr[1].first = arr[2].first = 2
```

### `count`

```cpp
template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
    count (InputIterator first, InputIterator last, const T& val);
```

在序列中找这个val，这个很好理解

```cpp
// count
std::vector<char> arr = {'a', 'b', 'c', 'd', 'e', 'a'};
std::cout << std::count(arr.begin(), arr.end(), 'a') << std::endl; // 2
```
输出：
```bash
2
```

### `count_if`

和`count`差不多，就是把val换成一个判断的函数。计算满足符合条件的元素的个数

```cpp
// count_if
// 计算小于0的元素的个数
std::vector<int> arr1 = {-1, 0, 4, 7, -4, 8, -10, 2, 6, 9};
std::cout << std::count_if(arr1.begin(), arr1.end(), [](int i)
                        { return i < 0; })
            << std::endl; // 3
```

输出是3。

### `mismatch`

将范围`[first1，last1)`中的元素与从first2开始的范围中的元素进行比较，并返回两个序列中第一个不匹配的元素。
返回的这两个数放在pair里面。

```cpp
template <class InputIterator1, class InputIterator2>
  pair<InputIterator1, InputIterator2>
    mismatch (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2);	
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  pair<InputIterator1, InputIterator2>
    mismatch (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate pred);
```

例子：
```cpp
void test7()
{
    // mismatch
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::vector<int> arr2 = {1, 2, 4, 3};
    auto p = std::mismatch(arr1.begin(), arr1.end(), arr2.begin());
    std::cout << "the first mismatched element in to list: " << *(p.first) << ":" << *(p.second) << std::endl;
}
```
输出：
```bash
the first mismatched element in to list: 3:4
```

### `equal`

```cpp
template <class InputIterator1, class InputIterator2>
  bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2);
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate pred);
```
两个序列完全一样才返回true。

例子：

```cpp
void test7()
{
    // mismatch
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::vector<int> arr2 = {1, 2, 4, 3};
    auto p = std::mismatch(arr1.begin(), arr1.end(), arr2.begin());
    std::cout << "the first mismatched element in to list: " << *(p.first) << ":" << *(p.second) << std::endl;
    // equal
    std::cout << std::equal(arr1.begin(), arr1.end(), arr2.begin()) << std::endl;
}
```
输出：

```
the first mismatched element in to list: 3:4
0
```

### `is_permutation`

看看第二个序列是否是第一个序列的排列。这个也是很好理解的。
和equal的区别其实就是，检查排列是不同order也是可以的。

```cpp
template <class ForwardIterator1, class ForwardIterator2>
   bool is_permutation (ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2);
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
   bool is_permutation (ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, BinaryPredicate pred);
```

例子：

```cpp
// is_permutation
std::vector<int> arr3 = {1, 2, 3};
std::vector<int> arr4 = {2, 1, 3};
std::cout << std::is_permutation(arr3.begin(), arr3.end(), arr4.begin()) << std::endl;
```

输出是1。

### `search`

在范围`[first1，last1)`中搜索`[first2，last2)`定义的序列的第一个出现项，并将迭代器返回到其匹配的第一个元素，如果未找到出现项，则返回last1。

```cpp
template <class ForwardIterator1, class ForwardIterator2>
   ForwardIterator1 search (ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2);
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
   ForwardIterator1 search (ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            BinaryPredicate pred);
```

例子：
```cpp
void test8()
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> sub_arr = {2, 3, 4};
    auto it = std::search(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end());
    std::cout << *it << std::endl;
}
```

输出为2。

### `search_n`

寻找有连续count个val的子序列，返回第一个val的迭代器。

```cpp
template <class ForwardIterator, class Size, class T>
   ForwardIterator search_n (ForwardIterator first, ForwardIterator last,
                             Size count, const T& val);
predicate (2)	
template <class ForwardIterator, class Size, class T, class BinaryPredicate>
   ForwardIterator search_n ( ForwardIterator first, ForwardIterator last,
                              Size count, const T& val, BinaryPredicate pred );
```

例子：
```cpp
// search_n
std::vector<int> arr2 = {1, 2, 2, 2, 2, 3, 3, 4, 5};
auto it2 = std::search_n(arr2.begin(), arr2.end(), 3, 2); // 找连续的3个2
auto it3 = std::search_n(arr2.begin(), arr2.end(), 3, 3); // 找连续的3个3 -- 这个是找不到的
std::cout << *it2 << std::endl; // 2
std::cout << *it3 << std::endl; // 0
```
结果是2和0。


## 修改序列操作

### `copy`

```cpp
template <class InputIterator, class OutputIterator>
  OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result);
```

把第一个迭代器区间的东西拷贝到第二个迭代器区间上去。

例子：

```cpp
std::list<int> lst1 = {1, 2, 3, 4, 5};
std::vector<int> arr(lst1.size(), 0); // 要提前扩容，不然就会段错误
std::copy(lst1.begin(), lst1.end(), arr.begin());
print(arr);
```

输出：`1 2 3 4 5`

### `copy_n`

```cpp
template <class InputIterator, class Size, class OutputIterator>
  OutputIterator copy_n (InputIterator first, Size n, OutputIterator result);
```
拷贝前n个到第二个迭代器区间去，很好理解。

```cpp
// copy_n
std::vector<int> arr2(4, 0);
std::copy_n(lst1.begin(), 3, arr2.begin() + 1); // 拷贝到arr2的第二个位置去
print(arr2);
```

输出为：`0 1 2 3`

### `copy_if`

拷贝序列1中符合条件的元素到第二个迭代器上。

```cpp
template <class InputIterator, class OutputIterator, class UnaryPredicate>
  OutputIterator copy_if (InputIterator first, InputIterator last,
                          OutputIterator result, UnaryPredicate pred);
```

例子：
```cpp
// copy_if
std::vector<int> arr3(5, 0);
std::copy_if(lst1.begin(), lst1.end(), arr3.begin(), [](int i)
                { return i <= 3; });
print(arr3);
```

输出为：`1 2 3 0 0`

### `copy_backward`

也是复制序列。但是输出的迭代器是给一个输出序列区间的end()位置。反着来拷贝

比如：`int a[] = {1,2,3,4,5}`
如果想把a拷贝到b中，那就要传一个b.end()迭代器，然后从5开始拷贝，但是最后拷贝出来的序列也是正序的。

看看例子就明白了。

```cpp
// copy_backward
std::list<int> lst2 = {1, 2, 3};
std::vector<int> arr4(lst2.size() + 1, 0);
std::copy_backward(lst2.begin(), lst2.end(), arr4.end());
print(arr4); // 0 1 2 3
```

输出为：`0 1 2 3`

### `move`

```cpp
template <class InputIterator, class OutputIterator>
  OutputIterator move (InputIterator first, InputIterator last, OutputIterator result);
```

从一个迭代器区间移动到另一个迭代器区间上。

```cpp
void test2()
{
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2(arr1.size(), 0);
    std::move(arr1.begin(), arr1.end(), arr2.begin());
    print(arr1); // BUG
    print(arr2);
}
```
输出：
```
1 2 3 4 5 
1 2 3 4 5
```

移动完之后，被移动后的空间就是剩下的**不确定的合法态**。

### `move_backward`

这个和上面是一样的，和`copy_backward`是一个道理。

```cpp
// move_backward
std::vector<int> arr3(arr1.size() + 1, 0);
std::move_backward(arr1.begin(), arr1.end(), arr3.end());
print(arr1);
print(arr3);
```
输出：
```
1 2 3 4 5 
0 1 2 3 4 5 
```

### `swap`

交换两个元素。

```cpp
template <class T> void swap (T& a, T& b);
```

例子：
```cpp
// swap
int a = 10;
int b = 20;
std::cout << "a: " << a << ", b: " << b << std::endl;
std::swap(a, b);
std::cout << "a: " << a << ", b: " << b << std::endl;
```

输出：
```
a: 10, b: 20
a: 20, b: 10
```

### `swap_ranges`

交换两个迭代器区间的元素。

```cpp
template <class ForwardIterator1, class ForwardIterator2>
  ForwardIterator2 swap_ranges (ForwardIterator1 first1, ForwardIterator1 last1,
                                ForwardIterator2 first2);
```

例子：
```cpp
// swap_ranges
std::vector<int> s1 = {1, 2, 3, 4, 5};
std::vector<int> s2 = {10, 20, 30, 40, 50};
std::swap_ranges(s1.begin(), s1.end(), s2.begin());
print(s1);
print(s2);
```
输出：
```
10 20 30 40 50 
1 2 3 4 5 
```

### `iter_swap`

```cpp
template <class ForwardIterator1, class ForwardIterator2>
  void iter_swap (ForwardIterator1 a, ForwardIterator2 b);
```

交换两个迭代器指向的元素，这个也是很好理解的。

```cpp
// iter_swap
std::vector<int> s3 = {1, 2, 3};
std::vector<int> s4 = {3, 2, 1};
std::iter_swap(s3.begin(), s4.begin());
print(s3);
print(s4);
```

输出：
```
3 2 3 
1 2 1 
```

### ``

```cpp
template <class InputIterator, class OutputIterator, class UnaryOperation>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperation op);
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class BinaryOperation>
  OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, OutputIterator result,
                            BinaryOperation binary_op);
```

这个函数有两种形式：
- 第一种就是让`[first1, last1)`的元素去进行op操作，然后存到result开始的位置上
- 第二种就是让`[first1, last1)`和first2开始的两个序列，同时进行个binary_op操作，然后结果存到result里面去

看例子就能明白了。

第一个例子就是让序列里面的元素都++一下，然后存到结果序列中。
第二个例子就是让两个序列的元素相加，然后存到结果序列中。

```cpp
void test4()
{
    // transform
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2(arr1.size(), 0);
    std::transform(arr1.begin(), arr1.end(), arr2.begin(), add());
    print(arr2);                            // 2,3,4,5,6
    std::vector<int> arr3(arr1.size(), 10); // 10,10,10,10,10
    std::vector<int> arr4(arr1.size(), 0);
    std::transform(arr1.begin(), arr1.end(), arr3.begin(), arr4.begin(), std::plus<int>());
    print(arr4); // 11,12,13,14,15
}
```

输出为：

```
2 3 4 5 6 
11 12 13 14 15 
```

### `replace`

```cpp
template <class ForwardIterator, class T>
  void replace (ForwardIterator first, ForwardIterator last,
                const T& old_value, const T& new_value);
```

把序列里面所有的old_value替换成new_value

```cpp
// replace
std::vector<int> arr1 = {1, 2, 2, 2, 3, 3, 3, 4, 5};
std::replace(arr1.begin(), arr1.end(), 2, 10);
print(arr1);
```

输出为：`1 10 10 10 3 3 3 4 5`

### `replace_if`

```cpp
template <class ForwardIterator, class UnaryPredicate, class T>
  void replace_if (ForwardIterator first, ForwardIterator last,
                   UnaryPredicate pred, const T& new_value );
```

把符合条件的换成new_value。也是很好理解的。

```cpp
// replace_if
std::vector<int> arr2 = {-1, -1, -2, -4, 0, 2, 3};
std::replace_if(
    arr2.begin(), arr2.end(), [](int i)
    { return i < 0; },
    100);
print(arr2); // 把 <0 的换成 100
```

输出为：`100 100 100 100 0 2 3 `


### `replace_copy`

这个和`replace`其实是一样的，只不过是这个替换完是存到别的地方上去而已。

例子：
```cpp
// replace_copy
std::vector<int> arr3 = {1, 2, 2, 2, 3, 3, 3, 4, 5};
std::vector<int> res(arr3.size(), 0);
std::replace_copy(arr3.begin(), arr3.end(), res.begin(), 2, 10);
print(res);
```

输出：`1 10 10 10 3 3 3 4 5`

### `replace_copy_if`

这个和`replace_if`其实是一样的，就是结果输出到别的地方而已

```cpp
// replace_copy_if
std::vector<int> arr4 = {-1, -1, -2, -4, 0, 2, 3};
std::vector<int> res2(arr4.size(), 0);
std::replace_copy_if(
    arr4.begin(), arr4.end(), res2.begin(), [](int i)
    { return i < 0; },
    100);
print(res2);
```

输出：`100 100 100 100 0 2 3 `

### `fill`

```cpp
template <class ForwardIterator, class T>
  void fill (ForwardIterator first, ForwardIterator last, const T& val);
```

用val去填充迭代器区间。

```cpp
std::vector<int> arr1(5, 0);
std::fill(arr1.begin(), arr1.end(), 10);
print(arr1);
```

输出：`10 10 10 10 10`

### `fill_n`

用n个val去填充迭代器区间，传一个begin位置就行。

例子：

```cpp
// fill_n
std::vector<int> arr2(5, 0);
std::fill_n(arr2.begin(), 4, 1); // 用4个1去填充
print(arr2);
```

输出：`1 1 1 1 0`

### `generate`

传入一个迭代器区间+生成器，生成一个序列。

看例子就能明白了：

```cpp
struct generator
{
    int number = 0;
    int operator()() { return ++number; }
};
void test7()
{
    // generate
    std::vector<int> arr1(5);
    std::generate(arr1.begin(), arr1.end(), generator());
    print(arr1);
}
```

输出：`1 2 3 4 5`

### `remove`

```cpp
template <class ForwardIterator, class T>
  ForwardIterator remove (ForwardIterator first, ForwardIterator last, const T& val);
```

删除迭代器区间的val

例子：

```cpp
std::vector<int> arr1 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
std::cout << "before calling remove, size: " << arr1.size() << std::endl;
auto new_end = std::remove(arr1.begin(), arr1.end(), 2);
std::cout << "after calling remove, size: " << arr1.size() << std::endl;
print(arr1.begin(), new_end);
```

注意：这里是把后面的数字往前挪动，因此返回来的新的结束位置的迭代器很重要。

remove调用完之后vector大小还是不变的。

输出：
```
before calling remove, size: 17
after calling remove, size: 17
1 3 5 6 5 7 8 
```

### `remove_if`

把符合条件的进行删除。

例子：
```cpp
// remove_if
std::vector<int> arr2 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
auto new_end2 = std::remove_if(arr2.begin(), arr2.end(), [](int i)
                                { return i == 2; });
print(arr2.begin(), new_end2);
```

输出：`1 3 5 6 5 7 8 `

### `remove_copy`

和`remove`同样，只是结果存到别的地方去而已。

```cpp
// remove_copy
std::vector<int> arr1 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
std::vector<int> arr2(arr1.size());
auto new_end = std::remove_copy(arr1.begin(), arr1.end(), arr2.begin(), 2);
print(arr2);
print(arr2.begin(), new_end);
```

输出：
```
1 3 5 6 5 7 8 0 0 0 0 0 0 0 0 0 0 
1 3 5 6 5 7 8 
```

### `remove_copy_if`

和`remove_if`同样，只是结果存到别的地方去而已。

```cpp
// remove_copy_if
std::vector<int> arr3 = {1, 2, 2, 3, 2, 2, 5, 6, 2, 2, 5, 2, 7, 8, 2, 2, 2};
std::vector<int> arr4(arr3.size());
auto new_end2 = std::remove_copy_if(arr3.begin(), arr3.end(), arr4.begin(), [](int i)
                                { return i == 2; });
print(arr4.begin(), new_end2);
```

输出：`1 3 5 6 5 7 8 `

### `unique`

```cpp
template <class ForwardIterator>
  ForwardIterator unique (ForwardIterator first, ForwardIterator last);
template <class ForwardIterator, class BinaryPredicate>
  ForwardIterator unique (ForwardIterator first, ForwardIterator last,
                          BinaryPredicate pred);
```

删除序列中**连续**重复的元素，只留下第一个。

```cpp
std::vector<int> arr1 = {1, 2, 2, 3, 3, 4, 3, 2, 5, 5, 8, 5, 9, 10, 2, 10};
std::unique(arr1.begin(), arr1.end());
print(arr1);
```
输出：`1 2 3 4 3 2 5 8 5 9 10 2 10 10 2 10`

### `unique_copy`

和`unique`其实是一样的，就是把结果放到别的地方去就行了。

```cpp
// unique_copy
std::vector<int> arr2 = {1, 2, 2, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 9, 9, 10, 10};
std::vector<int> res(arr2.size());
auto it = std::unique_copy(arr2.begin(), arr2.end(), res.begin());
print(res);
print(res.begin(), it); // 函数返回的迭代器也要注意一下
```

输出：
```
1 2 3 4 5 6 7 8 9 10 0 0 0 0 0 0 0 0 
1 2 3 4 5 6 7 8 9 10
```

### `reverse`

翻转一个迭代器区间序列的顺序。

```cpp
template <class BidirectionalIterator>
  void reverse (BidirectionalIterator first, BidirectionalIterator last);
```

例子：
```cpp
std::vector<int> arr1 = {1, 2, 3, 4};
std::reverse(arr1.begin(), arr1.end());
print(arr1);
```
输出：`4 3 2 1`

### `reverse_copy`

和`reverse`的区别就是输出到别的地方去。

```cpp
// reverse_copy
std::vector<int> arr2 = {1, 2, 3, 4};
std::vector<int> res(arr2.size());
std::reverse_copy(arr2.begin(), arr2.end(), res.begin());
print(res);
```

输出：`4 3 2 1`

### `rotate`

```cpp
template <class ForwardIterator>
  void rotate (ForwardIterator first, ForwardIterator middle,
               ForwardIterator last);
```

旋转一个序列，直到middle是第一个元素

```cpp
// rotate
std::vector<int> arr1 = {1, 2, 3, 4, 5, 6};
std::rotate(arr1.begin(), arr1.begin() + 3, arr1.end()); // 让4作第一个元素
print(arr1);
```

输出：`4 5 6 1 2 3`

### `rotate_copy`

和`rotate`的区别就是输出到别的地方去。

```cpp
// rotate_copy
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6};
std::vector<int> res(arr2.size());
std::rotate_copy(arr2.begin(), arr2.begin() + 3, arr2.end(), res.begin()); // 让4作第一个元素
print(res);
```

输出：`4 5 6 1 2 3`

### `random_shuffle`

```cpp
template <class RandomAccessIterator>
  void random_shuffle (RandomAccessIterator first, RandomAccessIterator last);
template <class RandomAccessIterator, class RandomNumberGenerator>
  void random_shuffle (RandomAccessIterator first, RandomAccessIterator last,
                       RandomNumberGenerator& gen);
```

随机打乱一个序列。

如果给了第三个参数gen，那就是按照gen作为种子来打乱，如果不给gen，就是随机打乱。

gen是一个函数对象，返回一个数字。

gen可以这样设计：
```cpp
int myrandom (int i) { return std::rand() % i;}
```

例子：
```cpp
// random_shuffle
std::vector<int> arr1 = {1, 2, 3, 4, 5, 6};
std::random_shuffle(arr1.begin(), arr1.end());
print(arr1);
```
输出：`5 4 2 3 1 6`

### `shuffle`

```cpp
template <class RandomAccessIterator, class URNG>
  void shuffle (RandomAccessIterator first, RandomAccessIterator last, URNG&& g);
```
也是打乱。
但是g要传一个C++的`uniform random number generator`

例子：
```cpp
// shuffle
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6};
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::shuffle(arr2.begin(), arr2.end(), std::default_random_engine(seed));
print(arr2);
```
输出：`1 6 2 4 3 5`

## 分区操作

### `is_partitioned`

```cpp
template <class InputIterator, class UnaryPredicate>
  bool is_partitioned (InputIterator first, InputIterator last, UnaryPredicate pred);
```

判断在一个序列中，满足pred的元素是否都在不满足pred的元素的前面。

例子：
```cpp
std::vector<int> arr1 = {1, 2, 3, 4, 5};
std::cout << std::is_partitioned(arr1.begin(), arr1.end(), [](int i)
                                  { return i <= 3; })
          << std::endl;
```

小于等于3的都在前面吗？

输出：`1`

### `partition`

```cpp
template <class BidirectionalIterator, class UnaryPredicate>
  BidirectionalIterator partition (BidirectionalIterator first,
                                   BidirectionalIterator last, UnaryPredicate pred);
```

把元素分组，满足pred的都放到前面，不满足pred的放到后面，返回第二组（不满足pred）的第一个元素的迭代器。

例子：
```cpp
// partition
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
std::partition(arr2.begin(), arr2.end(), [](int i)
                { return i % 2 == 0; });
print(arr2);
```
偶数放到前面来。
输出：`6 2 4 3 5 1 7`

### `stable_partition`

```cpp
template <class BidirectionalIterator, class UnaryPredicate>
  BidirectionalIterator stable_partition (BidirectionalIterator first,
                                          BidirectionalIterator last,
                                          UnaryPredicate pred);
```

稳定的分组：就是分组后，组内的元素的顺序和分组前是一样的。

例子：

```cpp
// stable_partition
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
std::stable_partition(arr2.begin(), arr2.end(), [](int i)
                { return i % 2 == 0; });
print(arr2);
```

输出：`2 4 6 1 3 5 7`


### `partition_copy`

```cpp
template <class InputIterator, class OutputIterator1,
          class OutputIterator2, class UnaryPredicate pred>
  pair<OutputIterator1,OutputIterator2>
    partition_copy (InputIterator first, InputIterator last,
                    OutputIterator1 result_true, OutputIterator2 result_false,
                    UnaryPredicate pred);
```

满足pred的元素，放到result_true中，不满足pred的元素，放到result_false中

返回的是两个迭代器，第一个指向result_true序列的end位置，另一个指向result_false序列的end位置。

```cpp
void test2()
{
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> odd(arr.size());  // 奇数
    std::vector<int> even(arr.size()); // 偶数
    auto p = std::partition_copy(arr.begin(), arr.end(), odd.begin(), even.begin(), [](int i)
                                 { return i % 2 == 1; });
    print(odd.begin(), p.first);
    print(even.begin(), p.second);
}
```

输出：
```
1 3 5 7 9 
2 4 6 8 10 
```

### `partition_point`

```cpp
template <class ForwardIterator, class UnaryPredicate>
  ForwardIterator partition_point (ForwardIterator first, ForwardIterator last,
                                   UnaryPredicate pred);
```

**找到已经分好区的序列**的分割点。

**找到分好区的序列中**，第一个不满足pred的元素。

前提是这个序列已经分好区了

```cpp
void test3()
{
    // partition_point
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    auto is_odd = [](int i)
    { return i % 2 == 1; };
    if (!std::is_partitioned(arr.begin(), arr.end(), is_odd))
        assert(false);
    auto point = std::partition_point(arr.begin(), arr.end(), is_odd);
    print(arr.begin(), point);
    print(point, arr.end());
}
```
输出：
```
1 3 5 7 9 
2 4 6 8 10
```

如果序列不是提前分好区的，调用partition_point就会导致结果错误。所以使用之前可以用is_partitioned线判断一下。

## 排序

### `sort`

```cpp
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

给序列进行排序。

没有comp的版本需要重载`operator<`。

例子：

```cpp
// sort
std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
std::sort(arr.begin(), arr.end());
print(arr);
std::sort(arr.begin(), arr.end(), std::greater<int>());
print(arr);
```

输出：
```
1 2 3 4 5 6 7 8 9 10 
10 9 8 7 6 5 4 3 2 1
```

### `stable_sort`

用法和`sort`一样，但是`stable_sort`是稳定排序。

```cpp
// sort
std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
std::stable_sort(arr.begin(), arr.end());
print(arr);
std::stable_sort(arr.begin(), arr.end(), std::greater<int>());
print(arr);
```

输出：
```
1 2 3 4 5 6 7 8 9 10 
10 9 8 7 6 5 4 3 2 1
```

### `partial_sort`

```cpp
template <class RandomAccessIterator>
  void partial_sort (RandomAccessIterator first, RandomAccessIterator middle,
                     RandomAccessIterator last);
template <class RandomAccessIterator, class Compare>
  void partial_sort (RandomAccessIterator first, RandomAccessIterator middle,
                     RandomAccessIterator last, Compare comp);
```

重新排列序列，排完之后，在middle之前的，按照comp的顺序排列好，middle之后的，顺序未知。

例子：
```cpp
std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
std::partial_sort(arr.begin(), arr.begin() + 4, arr.end());
print(arr);
```

输出：
```
1 2 3 4 9 7 5 6 8 10
```

### `partial_sort_copy`

```cpp
template <class InputIterator, class RandomAccessIterator>
  RandomAccessIterator
    partial_sort_copy (InputIterator first,InputIterator last,
                       RandomAccessIterator result_first,
                       RandomAccessIterator result_last);
template <class InputIterator, class RandomAccessIterator, class Compare>
  RandomAccessIterator
    partial_sort_copy (InputIterator first,InputIterator last,
                       RandomAccessIterator result_first,
                       RandomAccessIterator result_last, Compare comp);
```

把排好序的东西放到result数组里面去，但是放多少个，取决于result_first到result_last有多少个位置，从小开始放（默认）

例子：
```cpp
void test4()
{
    // partial_sort_copy
    std::vector<int> arr = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    std::vector<int> res(3);
    std::partial_sort_copy(arr.begin(), arr.end(), res.begin(), res.end(), std::greater<int>());
    print(res); // 10 9 8
}
```
输出：`10 9 8`

### `is_sorted`

```cpp
template <class ForwardIterator>
  bool is_sorted (ForwardIterator first, ForwardIterator last);
template <class ForwardIterator, class Compare>
  bool is_sorted (ForwardIterator first, ForwardIterator last, Compare comp);
```

判断序列是否排好序了

例子：
```cpp
std::vector<int> arr1 = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::cout << std::is_sorted(arr1.begin(), arr1.end()) << std::endl; // 0
std::cout << std::is_sorted(arr2.begin(), arr2.end()) << std::endl; // 1
```
输出是0和1。

### `is_sorted_until`

```cpp
template <class ForwardIterator>
  ForwardIterator is_sorted_until (ForwardIterator first, ForwardIterator last);
template <class ForwardIterator, class Compare>
  ForwardIterator is_sorted_until (ForwardIterator first, ForwardIterator last,
                                   Compare comp);
```

找到第一个乱序的元素的位置，第一个没有按照顺序的元素的位置。

例子：
```cpp
void test6()
{
    // is_sorted_until
    std::vector<int> arr1 = {1, 2, 3, 4, 5, -1, -2, 0};
    auto it = std::is_sorted_until(arr1.begin(), arr1.end());
    print(arr1.begin(), it);
    print(it, arr1.end());
}
```
输出：
```
1 2 3 4 5 
-1 -2 0 
```

### `nth_element`

```cpp
template <class RandomAccessIterator>
  void nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                    RandomAccessIterator last);
template <class RandomAccessIterator, class Compare>
  void nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                    RandomAccessIterator last, Compare comp);
```

重排序列，让重排后的第nth个元素就是有序序列中第nth个位置应该为的元素。

放一个例子大家就能懂了。

```cpp
// nth_element
std::vector<int> arr1 = {1, 2, 3, 4, 5, -1, -2, 0};
std::nth_element(arr1.begin(), arr1.end() - 1, arr1.end()); // 排列之后最后一个元素一定是5
print(arr1);
```
输出：`2 1 0 -2 -1 3 4 5`


## 二分查找

**这一部分都要要求给的序列都是有序的！基于有序进行二分查找，效率为Ologn**

### `lower_bound`

```cpp
template <class ForwardIterator, class T>
  ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                               const T& val);
template <class ForwardIterator, class T, class Compare>
  ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                               const T& val, Compare comp);
```

在有序序列中找到第一个不小于val的值，返回它的迭代器。

```cpp
void test1()
{
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    if (!std::is_sorted(arr.begin(), arr.end()))
        assert(false);
    auto it = std::lower_bound(arr.begin(), arr.end(), 3);
    print(it, arr.end());
}
```

输出：`3 4 5 6 `

### `upper_bound`

找到第一个比val大大值，返回它的迭代器。

```cpp
// lower_bound 和 upper_bound
std::vector<int> arr = {1, 2, 3, 4, 5, 6};
if (!std::is_sorted(arr.begin(), arr.end()))
    assert(false);
auto it = std::lower_bound(arr.begin(), arr.end(), 3);
print(it, arr.end());
auto it2 = std::upper_bound(arr.begin(), arr.end(), 3);
print(it2, arr.end());
```

输出：
```
3 4 5 6 
4 5 6 
```
这样lower_bound 和 upper_bound的区别就很明显了。

### `equal_range`

```cpp
template <class ForwardIterator, class T>
  pair<ForwardIterator,ForwardIterator>
    equal_range (ForwardIterator first, ForwardIterator last, const T& val);
template <class ForwardIterator, class T, class Compare>
  pair<ForwardIterator,ForwardIterator>
    equal_range (ForwardIterator first, ForwardIterator last, const T& val,
                  Compare comp);
```

找到可以包含序列中所有等于val的区间，返回迭代器区间，用pair装起来

```cpp
void test2()
{
    // equal_range
    std::vector<int> arr = {1, 2, 3, 3, 3, 4, 5, 6};
    auto p = std::equal_range(arr.begin(), arr.end(), 3); // 找到3的区间
    // 因为序列是有序的，所以同样的数字肯定都放在一起
    print(p.first, p.second);
}
```

输出：`3 3 3`

### `binary_search`

```cpp
template <class ForwardIterator, class T>
  bool binary_search (ForwardIterator first, ForwardIterator last,
                      const T& val);
template <class ForwardIterator, class T, class Compare>
  bool binary_search (ForwardIterator first, ForwardIterator last,
                      const T& val, Compare comp);
```

二分查找看看序列中是否有val。

```cpp
std::vector<int> arr = {1, 2, 3, 3, 3, 4, 5, 6};
std::cout << std::binary_search(arr.begin(), arr.end(), 4) << std::endl;
std::cout << std::binary_search(arr.begin(), arr.end(), 10) << std::endl;
```

输出：
```
1
0
```

## 合并

### `merge`

```cpp
template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        OutputIterator result);
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
  OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        OutputIterator result, Compare comp);
```

合并两个有序序列成一个有序序列。

**注意：给的两个序列必须是有序的。**

例子：
```cpp
std::vector<int> arr1 = {1, 3, 5, 7};
std::vector<int> arr2 = {2, 4, 9, 11};
std::vector<int> res(arr1.size() + arr2.size());
std::merge(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
print(res);
```

输出：`1 2 3 4 5 7 9 11`

### `inplace_merge`

把两个连续的有序序列merge之后放到原先的位置上
比如序列`[first,last)`中`[first, middle)`和`[middle last)`分别是有序序列，merge之后放到`[first,last)`中来。

例子：
```cpp
// inplace_merge
std::vector<int> arr1 = {1, 3, 5, 7};
std::vector<int> arr2 = {2, 4, 9, 11};
std::vector<int> before_inplace_merge = arr1;
for (auto it = arr2.begin(); it != arr2.end(); it++)
    before_inplace_merge.push_back(*it);
std::cout << "before_inplace_merge: ";
print(before_inplace_merge);
std::inplace_merge(before_inplace_merge.begin(), before_inplace_merge.begin() + arr1.size(), before_inplace_merge.end());
std::cout << "after_inplace_merge: ";
print(before_inplace_merge);
```
输出：
```
before_inplace_merge: 1 3 5 7 2 4 9 11 
after_inplace_merge: 1 2 3 4 5 7 9 11 
```

### `includes`

```cpp
template <class InputIterator1, class InputIterator2>
  bool includes ( InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, InputIterator2 last2 );
template <class InputIterator1, class InputIterator2, class Compare>
  bool includes ( InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, InputIterator2 last2, Compare comp );
```

如果第一个序列包含第二个序列所有元素，返回true。

```cpp
void test3()
{
    std::vector<int> sub_arr = {1, 3, 5, 7};
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    std::cout << std::includes(arr.begin(), arr.end(), sub_arr.begin(), sub_arr.end()) << std::endl;
}
```

输出为：`1`

### `set_union`

```cpp
template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result);
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
  OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result, Compare comp);
```

求两个序列的并集，重复的元素会被去掉

```cpp
// set_union
std::vector<int> arr1 = {1, 2, 3, 5, 7, 9, 11, 13};
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
std::vector<int> res(arr1.size() + arr2.size());
auto it = std::set_union(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
print(res.begin(), it);
```
输出：`1 2 3 4 5 6 7 9 11 13`

### `set_intersection`

求交集，用法和`set_union`一样。

```cpp
// set_intersection
std::vector<int> arr1 = {1, 2, 3, 5, 7, 9, 11, 13};
std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
std::vector<int> res(std::max(arr1.size(), arr2.size()));
auto it = std::set_intersection(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
print(res.begin(), it);
```
输出：`1 2 3 5 7`

### `set_difference`

用法和`set_union`一样。找到序列1中对比序列2没有的元素。

例子：
```cpp
void test6()
{
    // set_difference
    std::vector<int> arr1 = {1, 2, 3, 5, 7, 9, 11, 13};
    std::vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> res(std::max(arr1.size(), arr2.size()));
    auto it = std::set_difference(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res.begin(), it);
}
```
输出：
```
9 11 13
```

### `set_symmetric_difference`

和`set_difference`，`set_symmetric_difference`返回的是`并集-交集`，也就是两个序列中没有重复出现的元素

```cpp
void test7()
{
    // set_symmetric_difference
    std::vector<int> arr1 = {1, 2, 3, 4};
    std::vector<int> arr2 = {2, 3, 4, 5};
    std::vector<int> res(3);
    auto it = std::set_symmetric_difference(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), res.begin());
    print(res.begin(), it); // 1 5
}
```
输出：`1 5`

## 堆操作

下面的函数默认是大堆。

### `make_heap`

```cpp
template <class RandomAccessIterator>
  void make_heap (RandomAccessIterator first, RandomAccessIterator last);
custom (2)	
template <class RandomAccessIterator, class Compare>
  void make_heap (RandomAccessIterator first, RandomAccessIterator last,
                  Compare comp);
```

把一个序列排列成一个堆。复杂度是O(n)

例子：
```cpp
// make_heap
std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
std::make_heap(arr.begin(), arr.end());
print(arr);
```
输出：`5 4 1 2 3 0 1 2`

### `push_heap`

```cpp
template <class RandomAccessIterator>
  void push_heap (RandomAccessIterator first, RandomAccessIterator last);
template <class RandomAccessIterator, class Compare>
  void push_heap (RandomAccessIterator first, RandomAccessIterator last,
                   Compare comp);
```

序列的`[first,last-1)`已经是一个堆了，push_heap把`[first,last)`调整成堆。

为什么不用make_heap，make_heap也可以得到相同结果，因为make_heap是O(n)的操作。

push_heap是对最后一个元素做向上调整，swap次数最多为树的高度次，所以是Ologn的操作。

```cpp
void test2()
{
    // push_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    print(arr);
    arr.push_back(10);
    std::push_heap(arr.begin(), arr.end());
    print(arr);
}
```
输出：
```
5 4 1 2 3 0 1 2 
10 5 1 4 3 0 1 2 2 
```

### `pop_heap`

取序列中堆顶的元素，然后把堆顶元素从堆中去除，放到最后一个位置。`[first, last-1)`仍然是堆。

本质是让堆顶和最后一个元素交换，然后再对堆顶进行向下调整，复杂度为Ologn

```cpp
void test3()
{
    // pop_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    std::cout << "before pop: ";
    print(arr);
    std::pop_heap(arr.begin(), arr.end());
    std::cout << "after pop, whole list: ";
    print(arr);
    std::cout << "after pop, heap: ";
    arr.pop_back();
    print(arr);
}
```

输出：
```
before pop: 5 4 1 2 3 0 1 2 
after pop, whole list: 4 3 1 2 2 0 1 5 
after pop, heap: 4 3 1 2 2 0 1 
```

### `sort_heap`

把一个堆序列排列成升序，本质是堆排序，复杂度是Ologn

```cpp
void test4()
{
    // sort_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    print(arr);
    std::sort_heap(arr.begin(), arr.end());
    print(arr);
}
```
输出：
```
5 4 1 2 3 0 1 2 
0 1 1 2 2 3 4 5 
```

### `is_heap`

检查序列是否为堆。

```cpp
void test5()
{
    // is_heap
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::cout << std::is_heap(arr.begin(), arr.end()) << std::endl;
    std::make_heap(arr.begin(), arr.end());
    std::cout << std::is_heap(arr.begin(), arr.end()) << std::endl;
}
```

输出：
```
0
1
```

### `is_heap_until`

返回序列中第一个不满足堆序的元素的迭代器。

```cpp
void test6()
{
    // is_heap_until
    std::vector<int> arr = {1, 3, 5, 2, 4, 0, 1, 2};
    std::make_heap(arr.begin(), arr.end());
    arr.push_back(10);
    print(arr);
    auto it = std::is_heap_until(arr.begin(), arr.end());
    print(it, arr.end());
}
```

输出：
```
5 4 1 2 3 0 1 2 10 
10 
```

## min/max

### `min`和`max`

min的声明。max相同。
```cpp
template <class T> const T& min (const T& a, const T& b);
template <class T, class Compare>
  const T& min (const T& a, const T& b, Compare comp);
```

找到两个元素中较大的/较小的。

```cpp
void test1()
{
    int a = 10;
    int b = 20;
    std::cout << std::max(a, b) << std::endl;
    std::cout << std::min(a, b) << std::endl;
}
```
输出：
```
20
10
```

### `minmax`

```cpp
	
template <class T>
  pair <const T&,const T&> minmax (const T& a, const T& b);
template <class T, class Compare>
  pair <const T&,const T&> minmax (const T& a, const T& b, Compare comp);
initializer list (3)	
template <class T>
  pair<T,T> minmax (initializer_list<T> il);
template <class T, class Compare>
  pair<T,T> minmax (initializer_list<T> il, Compare comp);
```

返回两个元素中较小和较大的，或者返回初始化列表中最小和最大的。

```cpp
void test2()
{
    int a = 10;
    int b = 20;
    auto p1 = std::minmax(a, b);
    std::cout << p1.first << " " << p1.second << std::endl;
    auto p2 = std::minmax({1, 2, 3, 4, 5});
    std::cout << p2.first << " " << p2.second << std::endl;
}
```
输出：
```
10 20
1 5
```

### `min_element`和`max_element`

```cpp
template <class ForwardIterator>
  ForwardIterator max_element (ForwardIterator first, ForwardIterator last);
template <class ForwardIterator, class Compare>
  ForwardIterator max_element (ForwardIterator first, ForwardIterator last,
                               Compare comp);
```
min的也是同样的。

返回迭代器区间中最小的元素/最大元素的迭代器，很好理解直接上例子就行了。

```cpp
void test3()
{
    std::vector<int> arr = {1, 3, 5, 7, 2, 4, 6, 8, -1};
    std::cout << *std::max_element(arr.begin(), arr.end()) << std::endl;
    std::cout << *std::min_element(arr.begin(), arr.end()) << std::endl;
}
```
输出：
```cpp
8
-1
```

### `minmax_element`

```cpp
template <class ForwardIterator>
  pair<ForwardIterator,ForwardIterator>
    minmax_element (ForwardIterator first, ForwardIterator last);
template <class ForwardIterator, class Compare>
  pair<ForwardIterator,ForwardIterator>
    minmax_element (ForwardIterator first, ForwardIterator last, Compare comp);
```

返回序列中最小和最大的元素，装在pair里面。

```cpp
void test4()
{
    std::vector<int> arr = {1, 3, 5, 7, 2, 4, 6, 8, -1};
    auto p = std::minmax_element(arr.begin(), arr.end());
    std::cout << *p.first << " " << *p.second << std::endl;
}
```
输出：`-1 8`


## 其他

### `lexicographical_compare`

```cpp
template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2);
template <class InputIterator1, class InputIterator2, class Compare>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp);
```

如果第一个序列的字典序小于第二序列，返回true

```cpp
void test1()
{
    // lexicographical_compare
    std::vector<int> arr1 = {1, 2, -1, 1, 1, 1, 1};
    std::vector<int> arr2 = {1, 2, 1};
    std::cout << std::lexicographical_compare(arr1.begin(), arr1.end(), arr2.begin(), arr2.end()) << std::endl;
}
```

输出：`1`

### `next_permutation`

```cpp
template <class BidirectionalIterator>
  bool next_permutation (BidirectionalIterator first,
                         BidirectionalIterator last);
template <class BidirectionalIterator, class Compare>
  bool next_permutation (BidirectionalIterator first,
                         BidirectionalIterator last, Compare comp);
```

返回序列下一个字典序更大的排列，这个也是很好理解的，直接看例子。

如果有字典序更大的排列，返回true，否则返回false。

```cpp
void test2()
{
    // next_permutation
    std::vector<int> arr = {1, 2, 3, 4, 5};
    print(arr);
    std::cout << std::next_permutation(arr.begin(), arr.end()) << std::endl; // 是否有字典序更大的排列
    print(arr);
    std::vector<int> arr2 = {5, 4, 3};
    std::cout << std::next_permutation(arr2.begin(), arr2.end()) << std::endl; // 是否有字典序更大的排列
}
```
输出：
```
1 2 3 4 5 
1
1 2 3 5 4 
0
```

### `prev_permutation`

返回前一个排列。如果没有前一个排列了，返回false，否则返回true。如果是升序序列求prev_permutation就会返回false

其实就是next_permutation的反向操作

```cpp
void test3()
{
    // prev_permutation
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::cout << std::prev_permutation(arr.begin(), arr.end()) << std::endl;
}
```
输出：`0`