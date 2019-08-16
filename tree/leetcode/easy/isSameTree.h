//
//  isSameTree.h
//  tree
//
//  Created by junlongj on 2019/8/15.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isSameTree_hpp
#define isSameTree_hpp

#include <stdio.h>
#include "btree.h"
#include <queue>
/*
 100.相同的树
 给定两个二叉树，编写一个函数来检验它们是否相同。
 
 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
 
 示例 1:
 
 输入:       1         1
 / \       / \
 2   3     2   3
 
 [1,2,3],   [1,2,3]
 
 输出: true
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/same-tree
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    //先序遍历
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr){
            return true;
        }
        if (p == nullptr || q == nullptr){
            return false;
        }
        return p->val==q->val && isSameTree(p->lchild,q->lchild) && isSameTree(p->rchild,q->rchild);
    }
    //层次遍历
    bool isSameTree2(TreeNode* p, TreeNode* q){
        //层级遍历，先进先出
        std::queue<TreeNode *> q1,q2;
        q1.push(p);
        q2.push(q);
        while(!q1.empty() && !q2.empty()){
            TreeNode *a1 = q1.front();
            TreeNode *a2 = q2.front();
            q1.pop();
            q2.pop();
            if (!a1 && !a2)
                continue;
            if (!a1 || !a2)
                return false;
            if (a1->val != a2->val)
                return false;
            q1.push(a1->lchild);
            q2.push(a2->lchild);
            
            q1.push(a1->rchild);
            q2.push(a2->rchild);
        }
        return true;
    }
}
#endif /* isSameTree_hpp */
