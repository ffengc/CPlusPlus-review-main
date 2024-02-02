# 跳表手册

## Introduction

​	增加了向前指针的链表叫作跳表。跳表全称叫做跳跃表，简称跳表。跳表是一个随机化的数据结构，实质就是一种可以进行二分查找的有序链表。跳表在原有的有序链表上面增加了多级索引，通过索引来实现快速查找。跳表不仅能提高搜索性能，同时也可以提高插入和删除操作的性能。

​	跳表是一个随机化的数据结构，可以被看做二叉树的一个变种，它在性能上和红黑树，AVL树不相上下，但是跳表的原理非常简单，目前在Redis和LeveIDB中都有用到。

​	它采用随机技术决定链表中哪些节点应增加向前指针以及在该节点中应增加多少个指针。跳表结构的头节点需有足够的指针域，以满足可能构造最大级数的需要，而尾节点不需要指针域。

​	采用这种随机技术，跳表中的搜索、插入、删除操作的时间均为O(logn)，然而，最坏情况下时间复杂性却变成O(n)。相比之下，在一个有序数组或链表中进行插入/删除操作的时间为O(n)，最坏情况下为O(n)。

更详细的introduction、实现思路、效率复杂度分析、跳表和平衡树哈希表的对比见另一个文档：**[introduction.md](./introduction.md)**

## Manual

***

```cpp
template <class key_type, class value_type> class skip_list;
```

**跳表中的元素不允许重复。**

***

### 成员变量

| 成员变量名       | 成员变量定义    | note                   |
| ---------------- | --------------- | ---------------------- |
| `key_type`       | 第一个模版参数  | key-value数据中的key   |
| `value_type`     | 第二个模版参数  | key-value数据中的value |
| `iterator`       | 一个单向迭代器  |                        |
| `const_iterator` | const单向迭代器 |                        |

### 成员函数

#### 构造

```cc
skip_list();
template <class InputIterator>
skip_list(InputIterator first, InputIterator last);
skip_list(const std::initializer_list<std::pair<key_type, value_type>> &init_list);
skip_list(const skip_list<key_type, value_type> &lst)
```

**三种构造方式：**

- 无参数构造
- 迭代器区间构造
- 初始化列表构造
- 拷贝构造

#### 析构

```cpp
~skip_list();
```

析构时释放所有节点。

#### 迭代器

```cpp
iterator begin(); // 返回第一个元素的迭代器
iterator end();		// 返回最后一个元素的下一个位置的迭代器
const_iterator begin() const // 返回第一个元素的const迭代器
const_iterator end() const	 // 返回最后一个元素的下一个位置的const迭代器
```

#### `size`

```cc
size_t size() const;
```

返回跳表元素个数。

#### `clear`

```cc
void clear();
```

清除跳表中所有元素。

#### `empty`

```cc
bool empty() const;
```

判断跳表是否为空，如果为空，返回`true`，否则返回`false`。

#### `operator=`

```cc
skip_list<key_type, value_type> &operator=(const skip_list<key_type, value_type> &lst);
```

赋值重载，把另一个跳表的值复制到当前跳表中。

#### `find`

```cc
std::pair<value_type, bool> find(key_type target);
```

在跳表中查找键为`target`的元素，查找的平均效率为`O(logn)`。

返回找到的键为`target`的元素对应的值和表示查找是否成功的`bool`值所构成的`pair`。

#### `insert`

```cc
bool insert(std::pair<key_type, value_type> kv);
```

插入一个kv结构，返回值表示是否插入成功。

#### `erase`

```cc
bool erase(key_type key);
```

删除键为`key`的节点，返回值表示是否删除成功。