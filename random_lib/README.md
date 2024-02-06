# C++ `<random>` 头文件的学习

## 参考网站

- **[cplusplus.com](https://legacy.cplusplus.com/reference/random/)**

我针对这个文档链接里面的顺序进行了这个库的功能学习，并自己进行了一些demo的编写，都总结在下面了。

**文中部分文字来自于cplusplus.com**

## `<random>`库是干嘛的？

此头文件引入了随机数生成功能。这里面的功能对比C语言的随机数生成功能强大了很多。

**此库使用生成器和分布的组合生成随机数：**

- 生成器：生成均匀分布数字的对象。

- 分布：将生成器生成的数字序列转换为遵循特定随机变量分布（如均匀分布、正态分布或二项式分布）的数字序列的对象。

**简单demo解释**

使用流程：
1. 实例化一个生成器对象
2. 实例化一个分布器对象
3. 把生成器传给分布器
这样就能得到我们要的数字了

比如：
```cpp
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 6);
std::cout << distribution(generator) << std::endl;
```

当然如果说`distribution(generator)`形式一直写太麻烦，可以做参数和函数绑定。

```cpp
auto random_function = std::bind(distribution, generator);
std::cout << random_function() << std::endl;
```

除了`random_device`，库中定义的所有标准生成器都是随机数引擎，这是一种使用特定算法生成一系列伪随机数的生成器。这些算法需要一个种子作为随机性的来源，这个种子可以是单个值，也可以是具有特定`generate()`成员函数的对象（有关更多信息，请参阅`seed_seq`）。琐碎任务随机性的一个典型来源是时间，例如时间或`system_clock::now`提供的信息(有关典型示例，请参见`uniform_int_distribution::operator()`)。
[文字摘自cplusplus.com]


## Generators生成器

基于初始种子使用算法生成伪随机数的生成器。

### `linear_congruential_engine`

一种产生无符号整数的伪随机数生成器引擎。这是标准库中最简单的生成器引擎。其状态为单个整数值，具有以下转换算法：

$$
x = (a \cdot x + c) \text{mod} m
$$

一共有两个：
- minstd_rand0 这个是旧的
- minstd_rand 这个是新的

这两个都是**类模版**

我就只说`minstd_rand`了。

