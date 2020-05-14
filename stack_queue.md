# 栈&队列

栈是一种操作所限的线性表，只能在栈顶添加(push)或者删除元素(pop)，满足后进先出，先进后出的特性.

栈的底层既可以使用数组来实现，也可以用链表来实现，前者叫顺序栈，后者叫链表栈.

[栈的实现](./stack+queue/stack.h)

栈的应用:

- 函数堆栈
- 栈在表达式求值中的应用
- 栈在括号匹配中的应用({[]})


队列最大的特点就是先进先出，主要的两个操作是入队和出队。跟栈一样，它既可以用数组来实现，也可以用链表来实现。用数组实现的叫顺序队列，用链表实现的叫链式队列。特别是长得像一个环的循环队列。在数组实现队列的时候，会有数据搬移操作，要想解决数据搬移的问题，我们就需要像环一样的循环队列。

用链表实现的队列时一个无界队列，用数组实现的队列时一个有界队列。对于像线程池队列这种场景，系统的线程资源是有限的，使用有界队列更合理一些。

[队列的实现](./stack+queue/queue.h)


### [设计一个有getMin功能的栈(⭐️)](./stack+queue/leetcode/easy/MinStack.h)<br>

### [由两个栈组成的队列(⭐️⭐️)](./stack+queue/itinterviews/TwoStacksQueue.h)

###[<font color=red>如何仅用递归函数和栈操作逆序一个栈(⭐️⭐️)</font>](./stack+queue/itinterviews/reverseStack.h)

### [用一个栈实现另一个栈的排序(⭐️⭐️)](./stack+queue/itinterviews/sortStackByStack.h)

### [<font color=red>用栈来求解汉诺塔问题(⭐️⭐️⭐️)</font>](./stack+queue/itinterviews/hanoiProblem.h)

### [<font color=red>生成窗口最大值数组(⭐️⭐️)</font>](./stack+queue/itinterviews/getMaxWindow.h)

### [构建数组的MaxTree(❌❌)]()

### [求最大子矩阵的大小(❌❌)]()

### [最大值减去最小值小于或等于num的子数组数量(❌❌)]()




## leetcode
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  20   | [有限的括号](https://leetcode-cn.com/problems/valid-parentheses/)| [isValid](./stack+queue/leetcode/easy/isValid.h) | <font color=green>easy</font> | ✅ |
|  155   | [最小栈](https://leetcode-cn.com/problems/valid-parentheses)| [MinStack](./stack+queue/leetcode/easy/MinStack.h) | <font color=green>easy</font> | ✅ |
|  32   | [最长有效括号](https://leetcode-cn.com/problems/longest-valid-parentheses/)| [longestValidParentheses](./stack+queue/leetcode/longestValidParentheses.h) | ✨✨✨ | ✅ |
|  150   | [逆波兰表达式求值](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)| [evalRPN](./stack+queue/leetcode/evalRPN.h) | ✨✨  | ❌ |
|  641   | [设计循环双端队列](https://leetcode-cn.com/problems/design-circular-deque/)| [MyCircularDeque](./stack+queue/leetcode/MyCircularDeque.h) | ✨✨ | ❌ |
|  239   | [滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)| [maxSlidingWindow](./stack+queue/leetcode/maxSlidingWindow.h) | ✨✨✨ | ❌ |
       
## 剑指Offer
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  --   | [ 剑指Offer（五）：用两个栈实现队列](https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=13&tqId=11158&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)| [queueByStack](./stack+queue/coding-interviews/queueByStack.h) | ✨  | ✅  |  
