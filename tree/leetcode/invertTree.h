//
//  invertTree.h
//  tree
//
//  Created by junl on 2019/7/30.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef invertTree_hpp
#define invertTree_hpp

#include <stdio.h>

/*
 226.翻转一棵二叉树。
 
 示例：
 
 输入：
 
     4
   /   \
  2     7
 / \   / \
 1  3 6   9
 输出：
 
     4
   /   \
  7     2
 / \   / \
9   6 3   1
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/invert-binary-tree
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr)
        return nullptr;
    TreeNode *node = new TreeNode(root->val);
    node->lchild = invertTree(root->rchild);
    node->rchild = invertTree(root->lchild);
    return node;
}
namespace leetcode{
void test_invertTree(){
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
    
    
    TreeNode *root = invertTree(node4);
    root;
}
}
#endif /* invertTree_hpp */
