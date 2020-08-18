# 树


树的定义性质是，任意两个节点之间只有一条路径相连。 如果节点之间有多条路径或者没有路径相连则构成了图，而不是树。

树有很多种类型，我们从特殊到一般讨论它们的定义和表示:

- 二叉树和M叉树
- 有序树
- 有根树
- 自由树


也就是说: 

- 二叉树是一种特殊类型的有序数(它的每个节点最多2个节点)
- 有序数是一种特殊类型的有根树(比如它会指定每个节点的孩子顺序，比如二叉树依次是左孩子节点右孩子节点)
- 有根树是一种特殊类型的自由树(它有一个跟节点，是树的开始)


## 二叉树的数学性质

节点有三种类型： 

- 外部节点(就是叶子节点)
- 内部节点(除了前都是内部节点)


在开始数的算法之前，需要先了解二叉树相关的数学性质，有助用我们对算法性能的分析: 

- 一棵二叉树如果有N个内部节点，那么它就有N+1个外部节点
- 一棵二叉树如果有N个内部节点，则它有2N个链接，N-1链接到内部节点，N+1链接到外部节点(从跟到叶子节点的方向上看)
- 在一棵树中节点的层数比其父节点的层数要高一层（根节点在第0层），树的高度就是树中节点层数中的最大值。树的路径长度就是所有树节点的层数总和。在一棵二叉树的内部路径长度是树的所有内部节点的层数的总和，一棵二叉树的外部路径长度是树的所有外部节点的层数的总和.
- 任何带有N个内部节点的二叉树的外部路径长度比内部路径长度大2N
- 带有N个内部节点的二叉树的高度至少为lg(N), 至多为N-1. 最坏情况下，只有一个叶子节点，树的高度为N-1, 最好情况下是平衡二叉树，每一层数i的节点为2^i个内部节点(底部层数除外)
- 带有N个内部节点的二叉树的内部路径长度至少是N * lg(N / 4), 至多是N(N-1)/2


## 算法

关于树的算法题，重点要掌握以下这个:

- 前序，中序，后序的遍历
- 递归与回溯
- 二叉搜索树



二叉树的很多算法题都和树的遍历算法息息相关，选中合适的遍历方法就已经成功了一大半了，所以这是重点.

利用递归可以很容易的实现树的遍历，同样利用下推栈也能非常方便的实现. 这里我们构造一个特殊的节点能够保存数据项或者树的节点, 为了保持前序(根左右), 中序(左跟右)，后序(左右跟)遍历的顺序，我们进栈的顺序需要与之相反: 

- 对于前序, 我们先压入右子树，在压入左子树，最后是节点.
- 对于中序......
- 对于后序......

```
special_node *create_special_node_byitem(node *item){
    special_node *node = malloc(sizeof(*node));
    node->type = 0;
    node->node = item;
    return node;
}
special_node *create_special_node_bynode(node* n){
    special_node *node = malloc(sizeof(*node));
    node->type = 1;
    node->node = n;
    return node;
}
void pre_traverse_pushStk(stack *stk, node *head) {
    if (head->right) push(stk, create_special_node_bynode(head->right));
    if (head->left) push(stk, create_special_node_bynode(head->left));
    push(stk, create_special_node_byitem(head));
}
void in_traverse_pushStk(stack *stk, node *head) {
    if (head->right) push(stk, create_special_node_bynode(head->right));
    push(stk, create_special_node_byitem(head));
    if (head->left) push(stk, create_special_node_bynode(head->left));
}
void post_traverse_pushStk(stack *stk, node *head) {
    push(stk, create_special_node_byitem(head));
    if (head->right) push(stk, create_special_node_bynode(head->right));
    if (head->left) push(stk, create_special_node_bynode(head->left));
}

void traverse_stack(node *head, void(*visit)(node *), void(*push_stk)(stack*,node *)) {
    stack *stk = initStack(BUFSIZ);
    push_stk(stk, head);
    while (!isEmpty(stk)) {
        special_node *node = pop(stk);
        if (node->type == 0) {
            visit(node->node);
        }else{
            head = node->node;
            push_stk(stk, head);
        }
    }
}
void pre_traverse_stack(node *head, void(*visit)(node *)){
    traverse_stack(head, visit, pre_traverse_pushStk);
}
void in_traverse_stack(node *head, void(*visit)(node *)){
    traverse_stack(head, visit, in_traverse_pushStk);
}
void post_traverse_stack(node *head, void(*visit)(node *)){
    traverse_stack(head, visit, post_traverse_pushStk);
}
```

中序和后序的实现仅仅调整下入栈的三行代码的顺序即可. 除了构建特殊节点外，也可以使用下推栈实现: 

```
void pre_traverse_linear(node *head, void(*visit)(node *)){
    stack *stk = initStack(BUFSIZ);
    push(stk, head);
    while (!isEmpty(stk)) {
        visit((head = pop(stk)));
        if (head->right != NULL) push(stk, head->right);
        if (head->left != NULL) push(stk, head->left);
    }
}
void in_traverse_linear(node *tree, void(*visit)(node *)){
    stack *stk = initStack(BUFSIZ);
    while (tree != NULL || !isEmpty(stk)) {
        if (tree) {
            push(stk, tree);
            tree = tree->left;
        }else{
            tree = pop(stk);
            visit(tree);
            tree = tree->right;
        }
    }
}
void post_traverse_linear(node *tree, void(*visit)(node *)){
    stack *stk = initStack(BUFSIZ);
    stack *stk2 = initStack(BUFSIZ);
    push(stk, tree);
    while (!isEmpty(stk)) {
        tree = pop(stk);
        push(stk2, tree);
        if (tree->left != NULL) push(stk, tree->left);
        if (tree->right != NULL) push(stk, tree->right);
    }
    while (!isEmpty(stk2)) {
        tree = pop(stk2);
        visit(tree);
    }
}

void level_traverse(node *tree, void(*visit)(node *)){
    queue *q = initQueue(BUFSIZ);
    enQueue(q, tree);
    while (!isQEmpty(q)) {
        node *node = deQueue(q);
        visit(node);
        if (node->left)
            enQueue(q, node->left);
        if (node->right)
            enQueue(q, node->right);
    }
}
```

<b>树是一种递归性质的数据结构，因而它的许多任务都使用递归算法，通过处理根节点以及递归地处理其子树来处理一棵树，大部分都是三种遍历法的衍生. </b>

比如现在需要去构建一个竞赛树结构，叶子节点为所有参赛的选手，两两PK，赢的人放在父节点上，这样根节点就是最终获胜的队伍. 为了去构建这样一棵树，我们把参赛的队伍分成两部分，一部分放在左子树里，另一部分放在右子树里，这些子问题又可以递归求解，最终获取到左子树获胜的队伍和右子树获胜的队伍，两者的最大值就是最终获胜的队伍

```
node *construct_maxtree(char values[], int l, int r){
    node *node = createnode(values[l]);
    if (l == r) return node;
    
    int m, u, v;
    m = (l + r) / 2;
    node->left = construct_maxtree(values, l, m);
    node->right = construct_maxtree(values, m+1, r);
    u = node->left->item;
    v = node->right->item;
    if (u > v) node->item = u;
    else node->item = v;
    return node;
}
```





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
