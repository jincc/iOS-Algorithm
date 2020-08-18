## 递归

### 什么是递归？


试想一下电影院自己在第几排的场景, 想要知道我在第几排，那么就要去问前面的人他处于第几排，那么前面的人又怎么知道他自己在第几排呢？那自然是他也要去问他前面的人咯.

这就是递归的场景，去的过程叫做<font size=5 color=red>“递”</font>, 回来的过程叫做<font size=5 color=red>“归”</font>，有来有回。


![](./res/recursion_example.png)

<!--<font size=5 color=red>递归其实就是利用栈的数据结构，再加上一些简单的逻辑算法从而完成了问题的求解。只不过这个栈是由系统来提供的，我们只是无感知罢了.</font>-->



### 适合场景

满足下面两点：

* 一个问题的解可以分解为几个子问题(规模更小的问题)的解, 并且子问题和问题除了数据规模不一样，求解思路是完全一样的。
* 存在终止条件


那么如何编写递归代码呢？

关键在于找到将大问题分解为小问题的规律，写出递归公式，然后在推敲出终止条件。


递归代码简洁高效，非常容易理解。大部分递归代码都可以用迭代来实现，但是有些问题用迭代会非常麻烦，而利用递归的思想就非常简单了. 

比如下面我们通过迭代遍历链表:

```
void ll_traverse(link *h, void(*visit)(link *n)){
    if (h == NULL) return;
    visit(h);
    ll_traverse(h->next, visit);
}
void ll_traverseR(link *h, void(*visit)(link *n)){
    if (h == NULL) return;
    ll_traverseR(h->next, visit);
    visit(h);
}
```
逆序打印链表如果用迭代实现就比较麻烦, 相反使用递归就非常简单. 上面的代码, 我们把整个的打印任务分成两部分: 第一部分是打印当前节点的值，第二部分是打印链表剩余部分的值. 

我们把打印链表剩余部分的任务，看成是一个完整的子问题，那么先答应链表的剩余部分，在打印当前节点，自然就是逆序打印咯.

我们在处理递归子问题时，要假设当前任务已经被解决了，不要陷入脑补该子问题是如何解决的，因为子问题和原问题的解决方式都是一样的，只是规模更小而已. 


递归容易出现堆栈溢出，重复计算，函数调用耗时多，空间复杂度高等问题。一般嵌套比较少的场景可以使用递归。



### 表达式求值

表达式有三种，前缀表达式，中缀表达式，后缀表达式. 中缀表达式是我们书写程序的方式，计算机解释程序的时候，会把它转换成为前缀/后缀的方式. 那么如何转换&计算呢? 

将中缀式表达式转换为后缀式表达式, 常见的解决思路是使用栈这个数据结构

```
 如果碰到数字直接将其输出
 如果碰到左括号直接忽略，
 如果碰到运算符推入栈，
 如果碰到右括号则将栈顶元素写到输出中
 
```

碰到右括号表明运算符左右两个数字已经被处理了，所以运算符可以被弹出去了.


```
char *transferPostfixExpression(char *expr){
    int len = strlen(expr);
    char buf[len];
    int i,j;
    
    stack *stk  = initStack(len);
    for (i = 0, j = 0; i < len; i++) {
        if (expr[i] == ')'){
            buf[j++] = pop(stk);
            buf[j++] = ' ';
        }
        if (expr[i] == '+' || expr[i] == '*' || expr[i] == '/' || expr[i] == '-')
            push(stk, expr[i]);
        if (expr[i] >= '0' && expr[i] <= '9'){
            buf[j++] = expr[i];
            buf[j++] = ' ';
        }
    }
    while (!isEmpty(stk)) {
        buf[j++] = pop(stk);
    }
    buf[j] = '\0';
    return strdup(buf);
}

```

利用递归思想，也可以解决前缀/后缀表达式求值: 

前缀表达式的计算：

先读取一个运算符，然后依次读取两个运算数，并计算最终的值。这个运算数可以是一个number，也可以是一个子表达式: 


```
int evalPrefixExpression(char *expr, int *pos){
    while (expr[*pos] == ' ') {
        *pos+=1;
    }
    if (expr[*pos] == '+') {
        *pos+=1;
        return evalPrefixExpression(expr, pos) + evalPrefixExpression(expr, pos);
    }
    if (expr[*pos] == '*') {
        *pos+=1;
        return evalPrefixExpression(expr, pos) * evalPrefixExpression(expr, pos);
    }
    int val = 0;
    while (expr[*pos] >= '0' && expr[*pos] <= '9') {
        val = val * 10 + expr[*pos] - '0';
        *pos+=1;
    }
    return val;
}
```

后缀表达式定义: `expr1 expr2 op`, 其中`expr`有可能是另一个子后缀表达式. 所以后缀表达式的计算需要从后往前遍历,先取运算符，再取操作数, 这样就转换成了前缀表达式求值的问题了:


```
int evalPostExpression(char *expr, int *pos){
    if (*pos < 0) return -1;
    while (expr[*pos] == ' ') {
        (*pos)--;
    }
    int end = *pos;
    if (expr[*pos] == '+' || expr[*pos] == '*' || expr[*pos] == '-' || expr[*pos] == '/') {
        //说明当前元素是运算符
        --(*pos);
        int num2 = evalPostExpression(expr, pos);
        int num1 = evalPostExpression(expr, pos);
        if (expr[end] == '+') {
            return num1 + num2;
        }else if (expr[end]  == '*'){
            return num1 * num2;
        }else if (expr[end]  == '-'){
            return num1 - num2;
        }else {
            return num1 / num2;
        }
    }else{
        //说明当前是运算元
        int val = 0;
        int startPos, endPos;
        startPos = endPos = *pos;
        while (expr[startPos] >= '0' && expr[startPos] <= '9') {
            startPos--;
        }
        *pos = startPos;
        startPos++;
        
        //计算startPost到endPos之前的运算元
        for (; startPos<=endPos; startPos++) {
            val = val *10 + expr[startPos] - '0';
        }
        return val;
    }
}
```


<!--### [递归题目](./recursion.md)

### leetcode

| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  22   | [括号生成](https://leetcode-cn.com/problems/generate-parentheses/)| [generateParenthesis](./recursion/leetcode/medium/generateParenthesis.h) | ✨✨ | ✅ |
|  687   | [最长同值路径](https://leetcode-cn.com/problems/longest-univalue-path/)| [longestUnivaluePath](./recursion/leetcode/medium/longestUnivaluePath.h) | ✨✨ | ✅ |


### 剑指Offer
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  --   | [剑指Offer（七）：裴波那契数列](https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=13&tqId=11160&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)| [Fibonacci](./recursion/coding-interviews/Fibonacci.h) | ✨  | ✅  |
|  --   | [剑指Offer（八）：跳台阶]( https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=13&tqId=11161&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [jumpFloor](./recursion/coding-interviews/jumpFloor.h) | ✨  | ✅  |
|  --   | [剑指Offer（九）：变态跳台阶](https://www.nowcoder.com/practice/22243d016f6b47f2a6928b4313c85387?tpId=13&tqId=11162&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [jumpFloorII](./recursion/coding-interviews/jumpFloorII.h) | ✨ | ✅  |
|  --   | [剑指Offer（九）：变态跳台阶](https://www.nowcoder.com/practice/22243d016f6b47f2a6928b4313c85387?tpId=13&tqId=11162&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [jumpFloorII](./recursion/coding-interviews/jumpFloorII.h) | ✨| ✅  |
|  --   | [剑指Offer（十）：矩形覆盖]( https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=13&tqId=11160&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)| [rectCover](./recursion/coding-interviews/rectCover.h) | ✨  | ✅  |-->