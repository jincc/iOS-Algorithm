//
//  Mirror.h
//  tree
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef Mirror_hpp
#define Mirror_hpp

#include <stdio.h>
#include <queue>
/*
 剑指Offer（十八）：二叉树的镜像
 操作给定的二叉树，将其变换为源二叉树的镜像。
 
 https://www.nowcoder.com/practice/564f4c26aa584921bc75623e48ca3011?tpId=13&tqId=11171&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace  codinginterviews {
#pragma mark - 递归
     TreeNode* mirrorTree( TreeNode* root){
        if (root == NULL) return root;

        TreeNode *pleft = root->lchild;
        TreeNode *pright =  root->rchild;
        root->lchild = mirrorTree(pright);
        root->rchild = mirrorTree(pleft);
        return root;
    }
#pragma mark- 循环
    TreeNode* mirrorTree2( TreeNode* root){
        if (root == NULL) return root;
        
        std::queue<TreeNode *> stk;
        TreeNode *node =  NULL, *tmp = NULL;
        stk.push(root);
        while(!stk.empty()){
            node = stk.front();stk.pop();
            if (node->lchild) {
                stk.push(node->lchild);
            }
            if (node->rchild){
                stk.push(node->rchild);
            }
            tmp = node->lchild;
            node->lchild = node->rchild;
            node->rchild = tmp;
        }
        return root;
    }
    
    void test_Mirror(){
        std::cout << "test_Mirror starting......." << std::endl;
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
        
        mirrorTree2(node4);
        /*
         val: 4, isleaf: 0
         val: 7, isleaf: 0
         val: 2, isleaf: 0
         val: 9, isleaf: 1
         val: 6, isleaf: 1
         val: 3, isleaf: 1
         val: 1, isleaf: 1
         */
        btree::levelOrder(node4);
    }
}
#endif /* Mirror_hpp */
