//
//  longestUnivaluePath.h
//  recursion
//
//  Created by junlongj on 2019/8/30.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef longestUnivaluePath_hpp
#define longestUnivaluePath_hpp

#include <stdio.h>
#include "btree.h"
/*
 687.687. 最长同值路径
 给定一个二叉树，找到最长的路径，这个路径中的每个节点具有相同值。 这条路径可以经过也可以不经过根节点。
 
 注意：两个节点之间的路径长度由它们之间的边数表示。
 
 示例 1:
 
 输入:
 
    5
   / \
  4   5
 / \   \
1   1   5
 输出:
 
 2
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/longest-univalue-path
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    int maxPath = 0;
    /*
     思路:
     
     最长路径之和等于：左子树到跟的最长值 + 右子树到跟的最长值
     那左子树自己的最长值又如何求呢？r左子树自身也是由它的左子树和右子树构成的，这样递归就形成了。
     
     定义问题：
     1.怎样获取一个节点的最长单边路径（左子树到跟的最长值 或者 右子树到跟的最长值）
     2.最长路径 = 两边的最长单边路径之和
    
     maxUnivaluePath(root)表示节点(左或者)到root根节点的最长距离,比如图中:
     最左叶子节点到根节点:1->4->5 = 0
     最右叶子节点到根节点:5->5->5 = 2
     maxUnivaluePath(root) = 最长左边的距离+最长右边的距离
     */
    int maxUnivaluePath(TreeNode *root){
        if (!root)
            return 0;
        int leftPath = maxUnivaluePath(root->lchild);
        int rightPath = maxUnivaluePath(root->rchild);
        if (root->lchild && root->lchild->val == root->val){
            leftPath++;
        }else{
            leftPath = 0;
        }
        if (root->rchild && root->rchild->val == root->val){
            rightPath++;
        }else{
            rightPath=0;
        }
        maxPath = max(maxPath, leftPath + rightPath);
        return max(leftPath,rightPath);
    }
    int longestUnivaluePath(TreeNode* root) {
        maxUnivaluePath(root);
        return maxPath;
    }
    
}
#endif /* longestUnivaluePath_hpp */
