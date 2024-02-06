# C++ `<algorithm>` 头文件的学习

## 参考网站

- **[cplusplus.com](https://legacy.cplusplus.com/reference/random/)**

我针对这个文档链接里面的顺序进行了这个库的功能学习，并自己进行了一些demo的编写，都总结在下面了。

**文中部分文字来自于cplusplus.com**

标头`<algorithm>`定义了一组函数，这些函数专门设计用于迭代器。
迭代器是可以通过迭代器或指针访问的任何对象序列，例如一些STL容器的数组或实例。不过，请注意，算法直接通过迭代器对值进行操作，不会以任何方式影响任何可能的容器的结构（它永远不会影响容器的大小或存储分配）。

其实这些算法，把迭代器的优势发挥了出来，这就是封装、重载的魅力。

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



## 分区操作

## 排序

## 二分查找

## 合并

## 堆操作

## min/max

## 其他