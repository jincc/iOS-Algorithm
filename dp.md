# 动态规划



我们把问题的求解分成N个阶段，每个阶段对应一次选择，每次选择之后，会产生不同的状态，我们记录每个阶段的这些状态。然后通过当前的状态集合推导出下一阶段的状态集合，动态的向前推进。

就拿0-1背包问题来说，回溯和动态规划都能解决这个问题。只不过回溯算法解决起来的效率是很低的，时间复杂度是指数级别的，而动态规划在执行效率方面就提高很多，尽管执行效率提高了，但是动态规划的空间复杂度也提高了，所以很多时候我们会说动态规划是一种空间换时间的算法。



## 什么样的问题适合使用动态规划来解决？


step1: 首先看它是否属于<font size=5 color=red>多阶段决策最优解模型</font>，就是说解决问题的过程需要经历多个阶段，每个阶段决策之后会对应一组状态，然后我们寻找一组决策序列，经过这组决策序列，最终求出问题的最优解。

step2: 是否满足最优子结构，即是否能够从前面的状态推导出后面的状态。

step3: 是否满足无后效性，即前面状态一旦确定，就不会受之后阶段决策的影响。并且我们通过推到后面的状态的时候，只关心前面状态的值，而并不用关心它是怎么一步步推导出来的。

step4: 是否满足重复子问题，即当到达同一个阶段时是否存在多个状态.


## 动态规划的解题思路


关键点在于，<font size=5 color=red>如何定义状态，如何通过之前的状态推导出后面阶段的状态。</font>

对照着下面整个具体的例子，可以更好的去理解上面这些概念.


<font size=5 color=red>[matrix_move](./dp/matrix_move.h)</font>



### <font color=red>经典题型</font>

| &emsp;题型&emsp; |  答案链接 | 完成度 |
| :--: | :----------------------------------------------------------- | :--------: |
| 0-1背包问题及变种 | [knapsack](./dp/knapsack.h)|✅|
|  双11打折优惠问题 | [double11advance](./dp/double11advance.h)|✅|
|     硬币找零问题  | [coinChange2](./dp/coinChange.h)|✅|
|     杨辉三角变种 | [pascals_triangle](./dp/pascals_triangle.h)|✅|
|     矩阵从左上角移动到右下角 | [matrix_move](./dp/matrix_move.h)|✅|
|     莱文斯坦最短编辑距离  |  --  |❌|
| 两个字符串的最长公共子序列 |  --  |❌|
| 数据序列的最长递增子序列 |  --  | ❌|

### leetcode
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  64   | [最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)| [minPathSum](./dp/leetcode/minPathSum.h) | ✨✨ | ❌ |
|  10   | [正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/) | -- | ✨✨✨ | ❌ |
|  121  | [买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/) | -- | ✨ | ❌ |
|  152  | [乘积最大子序列](https://leetcode-cn.com/problems/maximum-product-subarray/) | -- | ✨✨ | ❌ |
|  120  | [三角形最小路径和](https://leetcode-cn.com/problems/triangle/) | -- | ✨✨ | ❌ |
|  70   | [爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)| [climbStairs](./dp/leetcode/easy/climbStairs.h) | <font color=green>easy</font> | ✅ |