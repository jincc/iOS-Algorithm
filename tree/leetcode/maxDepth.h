//
//  maxDepth.h
//  tree
//
//  Created by junl on 2019/8/1.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef maxDepth_hpp
#define maxDepth_hpp

#include <stdio.h>
/*
 104.给定一个二叉树，找出其最大深度。
 
 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
 
 说明: 叶子节点是指没有子节点的节点。
 
 示例：
 给定二叉树 [3,9,20,null,null,15,7]，
 
  3
 / \
 9  20
    /  \
   15   7
 返回它的最大深度 3 。
 
 
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/maximum-depth-of-binary-tree
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int leftDepth = maxDepth(root->lchild);
        int rightDepth = maxDepth(root->rchild);
        return std::max(leftDepth, rightDepth) + 1;
    }
}
#endif /* maxDepth_hpp */
