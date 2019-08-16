//
//  minDepth.h
//  tree
//
//  Created by junlongj on 2019/8/1.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef minDepth_hpp
#define minDepth_hpp

#include <stdio.h>

/*
 111.给定一个二叉树，找出其最小深度。
 
 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 
 说明: 叶子节点是指没有子节点的节点。
 
 示例:
 
 给定二叉树 [3,9,20,null,null,15,7],
 
     3
    / \
   9  20
      /  \
     15   7
 返回它的最小深度  2.
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/minimum-depth-of-binary-tree
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        if (root->lchild == nullptr && root->rchild == nullptr) {
            return 1;
        }
        int left = INT_MAX;
        if (root->lchild) {
            left = minDepth(root->lchild) + 1;
        }
        int right = INT_MAX;
        if (root->rchild) {
            right = minDepth(root->rchild) + 1;
        }
        return left < right ? left : right;
    }
    
    void test_minDepth(){
        TreeNode *node = new TreeNode(1);
        node->lchild = new TreeNode(2);
        std::cout << "minDepth staring...... \n" << minDepth(node) << std::endl;
    }
}

#endif /* minDepth_hpp */
