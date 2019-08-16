//
//  IsBalanced_Solution.h
//  tree
//
//  Created by junlongj on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef IsBalanced_Solution_hpp
#define IsBalanced_Solution_hpp

#include <stdio.h>

/*
 剑指Offer--039-平衡二叉树
 输入一棵二叉树，判断该二叉树是否是平衡二叉树。
https://www.nowcoder.com/practice/8b3b95850edb4115918ecebdf1b4d222?tpId=13&tqId=11192&tPage=2&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    /*
     平衡二叉树的定义：每一个节点，左右子树高度差不能超过1.
     
     解法一：暴力法
     */
    int getDepth(TreeNode *root){
        if (!root) return 0;
        return std::max(getDepth(root->lchild), getDepth(root->rchild)) + 1;
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return true;
        }
        int ldepth = getDepth(pRoot->lchild);
        int rdepth = getDepth(pRoot->rchild);
        if (abs(ldepth-rdepth) > 1) {
            return false;
        }else{
            return IsBalanced_Solution(pRoot->lchild) && IsBalanced_Solution(pRoot->rchild);
        }
    }
    /*
     解法二: 上面递归是从上到下的，所以有很多重复计算的问题，现在我们从下往上推断,通过后序遍历，遍历每个节点的时候，因为左右子树已经遍历过了，所以可以拿到左右子树的高度，从而进行判断。
     */
    bool IsBalanced_Solution2(TreeNode* pRoot, int *depth){
        if (pRoot == nullptr) {
            *depth = 0;
            return true;
        }
        int leftdepth;
        int rightdepth;
        if (IsBalanced_Solution2(pRoot->lchild, &leftdepth) &&
            IsBalanced_Solution2(pRoot->rchild, &rightdepth)) {
            *depth = std::max(leftdepth, rightdepth) + 1;
            if (abs(leftdepth-rightdepth) <= 1) {
                return true;
            }
        }
        return false;
        
    }
    bool IsBalanced_Solution2(TreeNode* pRoot){
        int depth;
        return IsBalanced_Solution2(pRoot, &depth);
    }
    
    void test_IsBalanced_Solution2(){
        std::cout << "test_IsBalanced_Solution2 starting........" << std::endl;
        TreeNode *node4 = new TreeNode(1);
        TreeNode *node2 = new TreeNode(2);
        TreeNode *node7 = new TreeNode(3);
        TreeNode *node1 = new TreeNode(4);
        TreeNode *node3 = new TreeNode(5);
        TreeNode *node6 = new TreeNode(3);
        TreeNode *node9 = new TreeNode(6);
        node4->lchild = node2;
        node4->rchild = node7;
        node2->lchild = node1;
        node2->rchild = node3;
        node7->lchild = node6;
        node7->rchild = node9;
        
        std::cout << IsBalanced_Solution2(node4) << std::endl;;
    }
}
#endif /* IsBalanced_Solution_hpp */
