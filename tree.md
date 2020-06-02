# 树

关于树的算法题，重点要掌握以下这个:

- 前序，中序，后序的遍历
- 递归与回溯
- 二叉搜索树


## 遍历

二叉树的很多算法题都和树的遍历算法息息相关，选中合适的遍历方法就已经成功了一大半了，所以这是重点.


[树的变量-递归&迭代](./tree/Tree.h)


## 递归和回溯

二叉树的大部分题型都是利用递归来解决的，使用递归重点在于: 第一确定递推公式，第二递归终止条件，除此之外，使用剪枝能提高很大一部分性能.


典型题型比如: 《路径总和》系列,leetcode 112, 113, 437


题目437和537题目解题思路有点类似，都是把二叉树的每个节点都当成是根节点，然后递归求最优解.

模板如下:

[437. 路径总和 III](https://leetcode-cn.com/problems/path-sum-iii/)

```
int dfs(struct TreeNode * root, int sum);
int pathSum(struct TreeNode* root, int sum){
    if (root == NULL) 
        return 0;
    return dfs(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}
int dfs(struct TreeNode * root, int sum){
    if (root == NULL) 
        return 0;
    sum -= root->val;
    int cnt = 0;
    if (sum == 0)
        cnt = 1;
    return dfs(root->left, sum) + dfs(root->right, sum) + cnt;
}
```





### leetcode

| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  94   | [二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)| [inorderTraversal](./tree/leetcode/inorderTraversal.h) | ✨✨ | ✅ |
|  98  | [验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/) | [isValidBST](./tree/leetcode/isValidBST.h) | ✨✨ | ✅ |
|  100  | [相同的树](https://leetcode-cn.com/problems/same-tree/) | [isSameTree](./tree/leetcode/easy/isSameTree.h) | <font color=green>easy</font> | ✅ |
|  104  | [二叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/) | [maxDepth](./tree/leetcode/maxDepth.h)  | ✨ | ✅ |
|  105   | [从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)| [buildTree](./tree/leetcode/buildTree.h)   | ✨✨ | ✅ |
|  111  | [二叉树的最小深度](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/) | [minDepth](./tree/leetcode/minDepth.h)   | ✨ | ✅ |
|  112  | [路径总和](https://leetcode-cn.com/problems/path-sum/) | [hasPathSum](./tree/leetcode/hasPathSum.h)  | ✨ | ✅ |
|  144  | [二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal) | [preorderTraversal](./tree/leetcode/preorderTraversal.h)  | ✨✨ | ✅ |
|  226  | [翻转二叉树](https://leetcode-cn.com/problems/invert-binary-tree/) | [invertTree](./tree/leetcode/invertTree.h)  | ✨ | ✅ |
|  230  | [二叉搜索树中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst) |[kthSmallestInTree](./tree/leetcode/kthSmallestInTree.h)  | ✨✨ | ✅ |
|  236  | [	二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/) | -- | ✨✨ | ❌ |
|  297  | [	二叉树的序列化与反序列化](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/) | -- | ✨✨✨ | ❌ |
|  429  | [ N叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/) | -- | ✨ | ❌ |
|  589  | [ N叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/) | -- | ✨ | ❌ |
|  590  | [ N叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/) | -- | ✨ | ❌ |


### 剑指offer
| &emsp;题号&emsp; | 题目链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| 答案链接&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;| &emsp;难度&emsp;  | &emsp;完成度&emsp;  |
| :--: | :--: | :----------------------------------------------------------- | :-----------------------------------------------------------  | :------: |
|  --   | [ 剑指Offer（十七）：树的子结构]( https://www.nowcoder.com/practice/6e196c44c7004d15b1610b9afca8bd88?tpId=13&tqId=11170&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [HasSubtree](./tree/coding-interviews/HasSubtree.h) | ✨  | ✅  |
|  --   | [ 剑指Offer（十八）：二叉树的镜像]( https://www.nowcoder.com/practice/564f4c26aa584921bc75623e48ca3011?tpId=13&tqId=11171&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)| [Mirror](./tree/coding-interviews/Mirror.h) | ✨ | ✅  |
|  --   | [剑指Offer（二十四）：二叉树中和为某一值的路径]( https://www.nowcoder.com/practice/b736e784e3e34731af99065031301bca?tpId=13&tqId=11177&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2)| [FindPath](./tree/coding-interviews/FindPath.h) | ✨ ✨ [注意]  | ✅  |
|  --   | [剑指Offer（三十九）：平衡二叉树]( https://www.nowcoder.com/practice/8b3b95850edb4115918ecebdf1b4d222?tpId=13&tqId=11192&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [IsBalanced_Solution](./tree/coding-interviews/IsBalanced_Solution.h) | ✨ ✨[注意]   | ✅  |
|  --   | [剑指Offer（五十七）：二叉树的下一个结点]( https://www.nowcoder.com/practice/9023a0c988684a53960365b889ceaf5e?tpId=13&tqId=11210&tPage=3&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [GetNext](./tree/coding-interviews/GetNext.h) | ✨✨✨[注意]  | ✅|
|  --   | [剑指Offer（五十八）：对称的二叉树](https://www.nowcoder.com/practice/ff05d44dfdb04e1d83bdbdab320efbcb?tpId=13&tqId=11211&tPage=3&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [isSymmetrical](./tree/coding-interviews/isSymmetrical.h) | ✨ | ✅|
|  --   | [剑指Offer（二十三）：二叉搜索树的后序遍历序列](https://www.nowcoder.com/practice/a861533d45854474ac791d90e447bafd?tpId=13&tqId=11176&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| [VerifySquenceOfBST](./tree/coding-interviews/VerifySquenceOfBST.h) | ✨ | ✅|
|  --   | [剑指Offer（二十六）：二叉搜索树与双向链表](https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&tqId=11179&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| -- | ✨ | ❌|
|  --   | [剑指Offer（六十二）：二叉搜索树的第k个结点](https://www.nowcoder.com/practice/ef068f602dde4d28aab2b210e859150a?tpId=13&tqId=11215&tPage=4&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking)| -- | ✨ | ❌ |
