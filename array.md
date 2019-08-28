## 数组
数组有两个关键词：

* 线性表结构， 就是说元素之间只有前后关系
* 连续的内存空间，存储的是具有相同类型的数据

第二个特征决定了数组<font size=5 color=red>“随机访问”</font>的能力，因为我们完全可以通过地址计算出下标对应的位置。比如:

<font size=5>a[i]_add = base_add + i * type_size</font>

有利就有弊，也正是由于内存连续，所以数组的插入和删除是非常低效的，因为为了保持内存的连续，就意味着每次插入/删除都要伴随着<font size=5 color=red>大量的移动操作</font>，平均负责度为o(n).


<font size=5 color=red>容器类</font>在数组的基础上，封装了插入删除等操作，同时支持了动态扩容. 需要注意的是，如果实现知道数组的大小，最好提前指定容器大小，这样可以省掉多次的内存申请和数据搬移。

大多情况下的<font size=5 color=red>解题思路</font>:

* 双指针
* DP
* 二分查找


### leetcode

| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  1| [两数之和](https://leetcode-cn.com/problems/two-sum/) | [twoSum](./array/leetcode/easy/twoSum.h) | <font color=green>easy</font> | ✅ |
|  26  | [删除排序数组中重复项](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/) | [removeDuplicates](./array/leetcode/easy/removeDuplicates.h)  | <font color=green>easy</font> | ✅ |
|  27  | [移除元素](https://leetcode-cn.com/problems/remove-element/submissions/) | [removeElement](./array/leetcode/easy/removeElement.h)  | <font color=green>easy</font> | ✅ |
|  35  | [搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/) | [searchInsert](./array/leetcode/easy/searchInsert.h)  | <font color=green>easy</font> | ✅ |
|  53  | [最大子序和](https://leetcode-cn.com/problems/maximum-subarray/) | [maxSubArray](./array/leetcode/easy/maxSubArray.h)  | <font color=green>easy</font> | ✅ |
|  66  | [加一](https://leetcode-cn.com/problems/plus-one/) | [plusOne](./array/leetcode/easy/plusOne.h) | <font color=green>easy</font> | ✅ |
|  88  | [合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/) | [merge](./array/leetcode/easy/merge.h) | <font color=green>easy</font> | ✅ |
|  118  | [杨辉三角](https://leetcode-cn.com/problems/pascals-triangle) | [pascals_triangle](./array/leetcode/easy/pascals_triangle.h) | <font color=green>easy</font> | ✅ |
|  119  | [杨辉三角2](https://leetcode-cn.com/problems/pascals-triangle-ii/) | [pascals_triangle_ii](./array/leetcode/easy/pascals_triangle_ii.h) | <font color=green>easy</font> | ✅ |
|  121  | [买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/) | [best_time_to_buy_and_sell_stock](./array/leetcode/easy/best_time_to_buy_and_sell_stock.h) | <font color=green>easy</font> | ✅ |
|  122 | [买卖股票的最佳时机ii](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/) | [best_time_to_buy_and_sell_stock_ii](./array/leetcode/easy/best_time_to_buy_and_sell_stock_ii.h) | <font color=green>easy</font> | ✅ |
|  167 | [两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/) | [twoSum_ii](./array/leetcode/easy/twoSum_ii.h) | <font color=green>easy</font> | ✅ |
|  169 | [求众数](https://leetcode-cn.com/problems/majority-element/) | [majorityElement](./array/leetcode/easy/majorityElement.h) | <font color=green>easy</font> | ✅ |
|  189  | [旋转数组](https://leetcode-cn.com/problems/rotate-array/) | [rotate](./array/leetcode/easy/rotate.h) | <font color=green>easy</font>  | ✅ |
|  11  | [盛最多水的容器](https://leetcode-cn.com/problems/container-with-most-water/) | [maxArea](./array/leetcode/maxArea.h) | ✨✨ | ✅ |
|  283  | [移动零](https://leetcode-cn.com/problems/move-zeroes/) | [moveZeroes](./array/leetcode/moveZeroes.h) | ✨ | ✅ |
|  15  | [三数之和](https://leetcode-cn.com/problems/3sum/) | [3sum](./array/leetcode/medium/3sum.h) | <font color=orange> medium </font> | ✅ |
|  16  | [最接近的三数之和](https://leetcode-cn.com/problems/3sum-closest) | [3SumClosest](./array/leetcode/medium/3SumClosest.h) | <font color=orange> medium </font> | ✅ |
|  39   | [组合总和](https://leetcode-cn.com/problems/combination-sum/)| [combinationSum](./array/leetcode/medium/combinationSum.h) |  <font color=orange> medium </font> | ✅|
### 剑指Offer
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  --   | [ 剑指Offer（一）：二维数组中的查找](https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&tqId=11154&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [Find](./array/coding-interviews/Find.h) | ✨ | ✅  |
|  --   | [剑指Offer（六）：旋转数组的最小数字]( https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=13&tqId=11159&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [minNumberInRotateArray](./array/coding-interviews/minNumberInRotateArray.h) | ✨  | ✅  |
|  --   | [剑指Offer（十三）：调整数组顺序使奇数位于偶数前面]( https://www.nowcoder.com/practice/beb5aa231adc45b2a5dcc5b62c93f593?tpId=13&tqId=11166&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [reOrderArray](./array/coding-interviews/reOrderArray.h) | ✨  | ✅  |
|  --   | [剑指Offer（二十八）：数组中出现次数超过一半的数字](  https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=13&tqId=11181&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [MoreThanHalfNum_Solution](./array/coding-interviews/MoreThanHalfNum_Solution.h) | ✨  | ✅  |
|  --   | [剑指Offer（三十）：连续子数组的最大和]( https://www.nowcoder.com/practice/459bd355da1549fa8a49e350bf3df484?tpId=13&tqId=11183&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)| -- | ✨  | ❌  |
|  --   | [剑指Offer（三十二）：把数组排成最小的数](https://www.nowcoder.com/practice/8fecd3f8ba334add803bf2a06af1b993?tpId=13&tqId=11185&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [PrintMinNumber](./array/coding-interviews/PrintMinNumber.h)  | ✨  | ✅  |
|  --   | [剑指Offer（三十七）：数字在排序数组中出现的次数](https://www.nowcoder.com/practice/70610bf967994b22bb1c26f9ae901fa2?tpId=13&tqId=11190&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [GetNumberOfK](./array/coding-interviews/GetNumberOfK.h)  | ✨ | ✅  |
|  --   | [剑指Offer（四十）：数组中只出现一次的数字](https://www.nowcoder.com/practice/e02fdb54d7524710a7d664d082bb7811?tpId=13&tqId=11193&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [FindNumsAppearOnce](./array/coding-interviews/FindNumsAppearOnce.h)  | ✨  | ✅  |