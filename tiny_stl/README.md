#  [`allocator`](http://www.cplusplus.com/reference/memory/allocator/?kw=allocator)

知识点:

- 利用定位new表达式来将内存分配和构造分开
- 学习`is_trivially_destructible`测试类型是否为普通易损坏类型, 如果是的话那么不需要调用其析构函数
    - 包括内置标量类型`is_scalar`
    - 还有一些特定的类（使用隐式的析构函数，它的成员本身也是普通易损坏类型）
- 明白forward的实现原理

实现:

- 实现allocator
- 实现forward完美转发


[`is_trivially_destructible`](http://www.cplusplus.com/reference/type_traits/is_trivially_destructible/?kw=is_trivially_destructible)<br>
[`forward`](http://www.cplusplus.com/reference/utility/forward/?kw=forward)<br>

#  [`pair`](http://www.cplusplus.com/reference/utility/pair/)

## decay

为什么需要衰减类型? 
当我们使用引用作为函数形参时，默认的转换规则时不生效的（比如数组转指针，函数转指针，去掉cv等）。使用decay允许在引用类型上发生这种类型转换. 

## enable_if

This is useful to hide signatures on compile time when a particular condition is not met, since in this case, the member enable_if::type will not be defined and attempting to compile using it should fail.



[`decay`](http://www.cplusplus.com/reference/type_traits/decay/)<br>
[`enable_if`](http://www.cplusplus.com/reference/type_traits/enable_if/?kw=enable_if)<br>
[`What is std::decay and when it should be used?`](https://www.it1352.com/460505.html)<br>



# [`iterator`](http://www.cplusplus.com/reference/iterator/)



根据功能划分为五种:
- input
- output
- forward
- Bidrectional
- RandomAcess

指针也算某种意义上的迭代器, 迭代器的操作它大多都支持.


## 萃取迭代器属性是如何做到的？

为了既支持萃取自定义迭代器又支持萃取指针迭代器的属性，`iterator_traits`采取了模板类的设计方式:

- 如果是指针迭代器，那么直接在模板类里面定义了类型成员
- 如果是普通迭代器，首先通过编译器静态检查，检查其是否包含`iterator_category`成员，并且检查该`iterator_category`成员是否是从基类`input_iterator_tag`或`out_iterator_tag`继承而来.



## 如何判断迭代器属于哪种类型？

通过萃取`iterator_category `属性然后判断属于五种中的哪一种





# [`type_traits `](https://www.cplusplus.com/reference/type_traits/)

C++的模板帮助我们在编写程序时不知道类型的情况，利用模板可以让我们定义出各种容器类和模板函数来复用代码。

而C++是静态语言，静态语言的类型检查是编译期进行的，为了约束我们的模板类/函数，标准库提供了[`type_traits `](https://www.cplusplus.com/reference/type_traits/)该头文件定义了一系列类，以获得有关编译时的类型信息。




# functional 《暂时跳过》

Function objects are objects specifically designed to be used with a syntax similar to that of functions. In C++, this is achieved by defining member function operator() in their class, like for example:

# [`vector`](https://www.cplusplus.com/reference/vector/vector/?kw=vector)

文档阅读:

- Only if T is guaranteed to not throw while moving, implementations can optimize to move elements instead of copying them during reallocations


# [`list`](http://www.cplusplus.com/reference/list/list/?kw=list)

- 底层双向列表实现，因此可以在任意位置常量时间插入/删除元素
- 缺点在于：每个元素都要存储一些额外数据用来定位，并且不能支持随机访问


- splice出了很多bug



# 暴露问题

- 模板编程
