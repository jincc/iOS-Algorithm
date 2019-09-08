#  二分查找

二分查找是在<font size=5 color=red>有序集合中快速寻找某个元素</font>的算法, 它的时间复杂度为O(logn)是一种非常高效的查找算法。<font size=5 color=red>二分查找每次都通过和区间的中间元素作对比，来将查找区间缩小为之前的一半，直到找到元素或区间缩小为一.</font>



二分适合的场景：

1. 二分查找依赖于数组结构的随机访问能力，对于其他数据结构无法适用。
2. 数组里面的元素必须是有序的，即如果我们是一次排序N次二分查找，那么可以平摊掉排序的时间，如果数据集合是频繁插入，删除，那么每次二分之前就需要先排序，在查找了，二分就不适合了.
3. 数据量太小不适合用二分查找，比如10次以内的循环，其实直接顺序遍历时间也差不多。但是如果涉及到元素比较比较耗时(比如长字符串直接的比较)，那么比较次数越少越好
4.  数据量太大也不适用于二分查找。因为二分需要依靠数组，而数组是无法存储大数据的。



## [二分查找基本代码](./bsearch/bsearch.h)

二分查找变形问题

## [查找第一个值等于给定值的元素](./bsearch/bsearch_findFirstElement.h)

## [查找最后一个值等于给定值的元素](./bsearch/bsearch_findLastElement.h)

## [ 查找第一个大于等于指定元素的值](./bsearch/bsearch_findFirstElementGreaterOrEqual.h)
## [查找最后一个小于等于给定值的元素](./bsearch/bsearch_findLastElementLessOrEqual.h)


在排序数组中寻找一个指定的数，我们既可以使用二分，也可以使用二叉树，散列表等数据结构。虽然后者会使用更多内存，但是当内存不是如此紧缺的情况下，使用后者也能做到。那么二分的优势何在呢？


<font size=5 color=red>二分法更适合用于“近似查找”问题</font>，比如刚刚的几个变种问题，如果使用散列表等结构就做不到了。


## leetcode
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  33   | [搜索旋转排序数组](https://leetcode-cn.com/problems/search-in-rotated-sorted-array)| [searchInRotatedSortedArray](./bsearch/leetcode/medium/searchInRotatedSortedArray.h) | ✨✨ | ✅|
|  50 | [Pow(x, n)](https://leetcode-cn.com/problems/powx-n/solution/powx-n-by-leetcode/) | [powx](./bsearch/leetcode/medium/powx.h) | <font color=orange> medium </font> | ✅ |
|  69   | [x 的平方根](https://leetcode-cn.com/problems/sqrtx/%E2%80%A8)| [mySqrt](./bsearch/leetcode/mySqrt.h) | ✨ | ✅ |
|  74 | [搜索二维矩阵](https://leetcode-cn.com/problems/search-a-2d-matrix/) | [search_a_2d_matrix](./bsearch/leetcode/medium/search_a_2d_matrix.h) | <font color=orange> medium </font> | ✅ |
|  81 | [搜索旋转排序数组II](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/) | [searchInRotatedSortedArrayII](./bsearch/leetcode/medium/searchInRotatedSortedArrayII.h) | <font color=orange> medium </font> | ✅ |
|  153 | [寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/) | [find_minimum_in_rotated_sorted_array](./bsearch/leetcode/medium/find_minimum_in_rotated_sorted_array.h) | <font color=orange> medium </font> | ✅ |
|  367   | [有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/)| [isPerfectSquare](./bsearch/leetcode/isPerfectSquare.h) | ✨ | ✅|