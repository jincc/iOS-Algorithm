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
/*
 剑指Offer（十八）：二叉树的镜像
 操作给定的二叉树，将其变换为源二叉树的镜像。
 
 https://www.nowcoder.com/practice/564f4c26aa584921bc75623e48ca3011?tpId=13&tqId=11171&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace  codinginterviews {
    void Mirror(TreeNode *pRoot) {
        if (pRoot == nullptr) {
            return;
        }
        TreeNode *left = pRoot->lchild;
        TreeNode *right = pRoot->rchild;
        pRoot->lchild = right;
        pRoot->rchild = left;
        Mirror(left);
        Mirror(right);
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
        
        Mirror(node4);
        btree::levelOrder(node4);
    }
}
#endif /* Mirror_hpp */
