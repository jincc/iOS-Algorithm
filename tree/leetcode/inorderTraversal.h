//
//  inorderTraversal.h
//  tree
//
//  Created by junl on 2019/7/30.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef inorderTraversal_hpp
#define inorderTraversal_hpp

#include <stdio.h>
#include <vector>
#include "btree.h"
/*
 94.给定一个二叉树，返回它的中序 遍历。
 
 示例:
 
 输入: [1,null,2,3]
 1
 \
 2
 /
 3
 
 输出: [1,3,2]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/binary-tree-inorder-traversal
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    void inorderTraversal(TreeNode* root, std::vector<int>  &inorder){
        if (root == nullptr) {
            return;
        }
        inorderTraversal(root->lchild, inorder);
        inorder.push_back(root->val);
        inorderTraversal(root->rchild, inorder);
    }
    
#pragma mark - 递归
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> inorder;
        inorderTraversal(root, inorder);
        return inorder;
    }
    
#pragma mark - 迭代
    std::vector<int> inorderTraversal2(TreeNode* root) {
        std::vector<int> inorder;
        std::vector<TreeNode *>nodes;
        while (!nodes.empty() || root != nullptr) {
            if (root) {
                nodes.push_back(root);
                root = root->lchild;
                //跟,左1,左左1.....
            }else{
                root = nodes.back();
                //先弹出最左边的.
                nodes.pop_back();
                inorder.push_back(root->val);
                //如果存在右子树，在处理右子树.
                root = root->rchild;
            }
        }
        return inorder;
    }
    

    void test_inorderTraversal(){
        std::cout << "test_inorderTraversal: starting......" << std::endl;
        
        TreeNode *root = new TreeNode(1);
        TreeNode *node1 = new TreeNode(2);
        TreeNode *node2 = new TreeNode(3);
        root->rchild = node1;
        node1->lchild = node2;
        std::vector<int> vec = inorderTraversal2(root);
        for (auto &c : vec){
            std::cout << c << ", " ;
        }
        std::cout << std::endl;
    }
}

#endif /* inorderTraversal_hpp */
