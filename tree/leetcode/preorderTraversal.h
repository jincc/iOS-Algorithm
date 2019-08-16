//
//  preorderTraversal.h
//  tree
//
//  Created by junlongj on 2019/8/1.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef preorderTraversal_hpp
#define preorderTraversal_hpp

#include <stdio.h>
#include <vector>

/*
 144.给定一个二叉树，返回它的 前序 遍历。
 
  示例:
 
 输入: [1,null,2,3]
   1
    \
     2
    /
   3
 
 输出: [1,2,3]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/binary-tree-preorder-traversal
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    
#pragma mark - 递归
    void preorderTraversal(TreeNode* root, std::vector<int> &nodes) {
        if (!root) {
        return;
        }
        nodes.push_back(root->val);
        preorderTraversal(root->lchild, nodes);
        preorderTraversal(root->rchild, nodes);
    }
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> nodes;
        preorderTraversal(root, nodes);
        return nodes;
    }
    
#pragma mark - 迭代
    std::vector<int> preorderTraversal2(TreeNode* root) {
        if (root == nullptr) return {};
        std::vector<int> ves;
        std::vector<TreeNode *> nodes;
        nodes.push_back(root);
        while (!nodes.empty()) {
            TreeNode *node = nodes.back();
            nodes.pop_back();
            ves.push_back(node->val);
            if (node->rchild) {
                nodes.push_back(node->rchild);
            }
            if (node->lchild) {
                nodes.push_back(node->lchild);
            }
        }
        return ves;
    }
    
    void test_preorderTraversal(){
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
        
        std::vector<int > r = preorderTraversal2(node4);
        r;
    }
}
#endif /* preorderTraversal_hpp */
