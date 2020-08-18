# 动态规划


前面说过，分治算法的本质就是将问题分解成两个独立的子问题， 如果子问题不能独立，那么解起来就非常麻烦了。 所以提出了另外一种避免这种缺陷的技术 -  动态规划.

为了避免子问题的重复计算，出现了`自顶向下的动态规划`, 它通过使用`meno`缓存来保存之前函数计算的结果来避免重复计算. `自底向上的动态规划`是它的逆过程, 我们把问题的求解分成N个阶段，每个阶段对应一次选择，每次选择之后，会产生不同的状态，我们记录每个阶段的这些状态。然后通过当前的状态集合推导出下一阶段的状态集合，动态的向前推进，它适用于任何递归计算. 它可以将算法的运行时间从递归的指数级减少到线性！


就拿0-1背包问题来说，回溯和动态规划都能解决这个问题。只不过回溯算法解决起来的效率是很低的，时间复杂度是指数级别的，而动态规划在执行效率方面就提高很多，尽管执行效率提高了，但是动态规划的空间复杂度也提高了，所以很多时候我们会说动态规划是一种空间换时间的算法。






## 什么样的问题适合使用动态规划来解决？


step1: 首先看它是否属于<font size=5 color=red>多阶段决策最优解模型</font>，就是说解决问题的过程需要经历多个阶段，每个阶段决策之后会对应一组状态，然后我们寻找一组决策序列，经过这组决策序列，最终求出问题的最优解。

step2: 是否满足最优子结构，即是否能够从前面的状态推导出后面的状态。

step3: 是否满足无后效性，即前面状态一旦确定，就不会受之后阶段决策的影响。并且我们通过推到后面的状态的时候，只关心前面状态的值，而并不用关心它是怎么一步步推导出来的。

step4: 是否满足重复子问题，即当到达同一个阶段时是否存在多个状态.


## 动态规划的解题思路


动态规划问题的一般形式就是`求最值`，比如说`最长递增子序列`，`最小编辑距离`等等，它们都符合`多阶段最优解模型`, 即问题的求解要分为多个阶段. `每个阶段怎么求出当前的最优值呢？` <font size=5 color=red>答案就是穷举</font>. 我们把当前阶段所有可行的答案穷举出来，然后从中找出最优解即可.


套路： 

1. 先确定「状态」，也就是原问题和子问题中变化的变量，每一次选择之后哪些变量变化了. 
2. 确定dp数组的定义
3. 每轮选择做出最优解, 穷举出当前阶段的所有可行的答案，然后求最优解.
4. 最后明确base case，即最小问题的答案.


第三步里面，最重要的点在于如何写出状态转移方程，只要写出了状态转移方程，那么就可以穷举出所有答案然后求最优。 写状态转移方程时，我们必须要先定义好「状态」，然后假设之前阶段的状态已获得，现在要做的就是怎么样通过之前的状态推导出现在的状态. 只要把这一点想明白了，状态转移方程自然就出来了。


```
int min(int x, int y){ return x < y ? x : y;}
int coinChange(int* coins, int coinsSize, int amount){
    if (coins == NULL || coinsSize <= 0) return 0;
    //定义状态
    int st[amount+1];
    memset(st, 0, sizeof(st));
    //每一轮都要做选择
    for(int i = 1; i <= amount; i++){
    	// 每次选择我们始终求最优的结果.
    	//获取最优解.
        int m_coin = INT_MAX;
        for(int j=0; j < coinsSize; j++){
            if (i >= coins[j] && st[i-coins[j]]!= -1){
                m_coin = min(m_coin, st[i-coins[j]] + 1);
            }
        }
        st[i] = m_coin == INT_MAX ? -1 : m_coin;
    }
    return st[amount];
}
```




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