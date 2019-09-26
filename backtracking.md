数独，八皇后，0-1背包，正则表达式, 图的着色，旅行商，全排列

---------------
# 回溯算法

回溯算法在很多时候都应用在"搜索"这类问题上,即<font size=5 color=red>在一组可能的解中，搜索满足期望的解.</font>


我们把问题的求解过程分成多个阶段，每一个阶段都会面对一个分叉路口，我们先随意选择一个路，当发现这条路走不通的时候，在回退到上一个分叉路口，选另一种走法继续走。另外可以通过<font size=5 color=red>剪枝</font>提高搜索效率.




# <font color=red>经典题型</font>

## [八皇后问题](./backtracking/eightQueens.h)
## [0-1背包问题](./backtracking/knapsack.h)
## [字符串匹配](./backtracking/Pattern.h)

### leetcode
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp; | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  17  | [电话号码的字母组合](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/) | [letter_combinations_of_a_phone_number](./backtracking/leetcode/medium/letter_combinations_of_a_phone_number.h) | <font color=orange> medium </font> | ✅ |
|  39   | [组合总和](https://leetcode-cn.com/problems/combination-sum/)| [combinationSum](./backtracking/leetcode/medium/combinationSum.h) |  <font color=orange> medium </font> | ✅|
|  40   | [组合总和II](https://leetcode-cn.com/problems/combination-sum-ii/)| [combinationSumII](./backtracking/leetcode/medium/combinationSumII.h) |  <font color=orange> medium </font> | ✅|
|  46   | [全排列](https://leetcode-cn.com/problems/permutations/)| [permutations](./backtracking/leetcode/medium/permutations.h) |  <font color=orange> medium </font> | ✅|
|  47   | [全排列II](https://leetcode-cn.com/problems/permutations-ii/)| [permutationsii](./backtracking/leetcode/medium/permutationsii.h) |  <font color=orange> medium </font> | ✅|
|  60   | [第k个排列](https://leetcode-cn.com/problems/permutation-sequence/)| [permutation_sequence](./backtracking/leetcode/medium/permutation_sequence.h) |  <font color=orange> medium </font> | ✅|
|  77   | [组合](https://leetcode-cn.com/problems/combinations/)| [combinations](./backtracking/leetcode/medium/combinations.h) |  <font color=orange> medium </font> | ✅|
|  78   | [子集](https://leetcode-cn.com/problems/subsets/)| [subsets](./backtracking/leetcode/medium/subsets.h) |  <font color=orange> medium </font> | ✅|
|  79   | [单词搜索](https://leetcode-cn.com/problems/word-search/)| [word_search](./backtracking/leetcode/medium/word_search.h) |  <font color=orange> medium </font> | ✅|
|  89   | [格雷编码](https://leetcode-cn.com/problems/gray-code/)| [gray_code](./backtracking/leetcode/medium/gray_code.h) |  <font color=orange> medium </font> | ✅|
|  90   | [子集II](https://leetcode-cn.com/problems/subsets-ii)| [subsets_ii](./backtracking/leetcode/medium/subsets_ii.h) |  <font color=orange> medium </font> | ✅|
|  93   | [复原IP地址](https://leetcode-cn.com/problems/restore-ip-addresses)| [restore_ip_addresses](./backtracking/leetcode/medium/restore_ip_addresses.h) |  <font color=orange> medium </font> | ✅|
### 剑指Offer
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  --   | [剑指Offer（六十五）：矩阵中的路径](https://www.nowcoder.com/practice/c61c6999eecb4b8f88a98f66b273a3cc?tpId=13&tqId=11218&tPage=4&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| -- | ✨  | ❌  |
|  --   | [剑指Offer（六十六）：机器人的运动范围](https://www.nowcoder.com/practice/6e5207314b5241fb83f2329e89fdecc8?tpId=13&tqId=11219&tPage=4&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| -- | ✨  | ❌  |
