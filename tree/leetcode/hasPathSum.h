//
//  hasPathSum.h
//  tree
//
//  Created by junlongj on 2019/8/1.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef hasPathSum_hpp
#define hasPathSum_hpp

#include <stdio.h>
#include <stack>
/*
 112.给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
 
 说明: 叶子节点是指没有子节点的节点。
 
 示例:
 给定如下二叉树，以及目标和 sum = 22，
 
     5
    / \
   4   8
  /   / \
 11  13  4
/  \      \
7   2      1
 返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。
 
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/path-sum
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    
#pragma mark - 递归
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == nullptr) {
            return false;
        }
        //如果是叶子节点的话,判断是否相等
        if (root->lchild == nullptr && root->rchild == nullptr &&
            sum == root->val){
            return true;
        }
        //否则要么存在于左子树，要么存在于右子树.
        return hasPathSum(root->lchild, sum - root->val) || hasPathSum(root->rchild, sum - root->val);
    }
#pragma mark - 深度优先遍历
    bool hasPathSum2(TreeNode* root, int sum){
        //每次遍历我们把路径的和记录在子节点上，最后判断叶子节点和sum是否相等.
        if (root == nullptr) {
            return false;
        }
        std::stack<TreeNode *> stk;
//        std::cout << "push: " << root->val << std::endl;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode *node =  stk.top();
            stk.pop();
//            std::cout << "pop: " << node->val << std::endl;
            if (node->lchild == nullptr && node->rchild == nullptr &&
                node->val == sum) {
                return true;
            }
            if (node->lchild) {
//                std::cout << "push: " << node->lchild-> val << std::endl;

                node->lchild->val += node->val;
                stk.push(node->lchild);
            }
            if (node->rchild) {
//                std::cout << "push: " << node->rchild->val << std::endl;

                node->rchild->val += node->val;
                stk.push(node->rchild);
            }
        }
        return false;
    }
    
    
    
    void test_hasPathSum(){
        std::cout << "hasPathSum starting........" << std::endl;
        TreeNode *node4 = new TreeNode(4);
        TreeNode *node2 = new TreeNode(2);
        TreeNode *node7 = new TreeNode(7);
        TreeNode *node1 = new TreeNode(1);
        TreeNode *node3 = new TreeNode(3);
        TreeNode *node6 = new TreeNode(6);
        TreeNode *node9 = new TreeNode(9);
        node4->lchild = node2;
        node4->rchild = node7;
        node2->lchild = node1;
        node2->rchild = node3;
        node7->lchild = node6;
        node7->rchild = node9;
        
        std::cout << hasPathSum2(node4, 17) << std::endl;
    }
}


#endif /* hasPathSum_hpp */
