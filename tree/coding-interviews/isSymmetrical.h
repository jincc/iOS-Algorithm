//
//  isSymmetrical.h
//  tree
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isSymmetrical_hpp
#define isSymmetrical_hpp

#include <stdio.h>
#include <vector>

/*
 剑指Offer（五十八）：对称的二叉树
 
 请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
https://www.nowcoder.com/practice/ff05d44dfdb04e1d83bdbdab320efbcb?tpId=13&tqId=11211&tPage=3&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
#pragma preorder
    bool isSymmetrical(TreeNode* left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr) {
            return true;
        }else if (left != nullptr && right!= nullptr){
            if (left->val != right->val) {
                return false;
            }
            //继续判断左右子树
            return isSymmetrical(left->lchild, right->rchild) && isSymmetrical(left->rchild, right->lchild);
        }else{
            return false;
        }
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
        return isSymmetrical(pRoot, pRoot);
    }
    
#pragma mark - level order
    bool isSymmetrical2(TreeNode *pRoot){
        if (pRoot == nullptr) return true;
        std::vector<TreeNode *> stk;
        stk.push_back(pRoot);
        while (!stk.empty()){
            int size = stk.size();
            int i=0;
            int j = size-1;
            while (i<j) {
                if (stk[i]->val != stk[j]->val) {
                    return false;
                }
                i++;
                j--;
            }
            if (i == j  && i!=0) {
                return false;
            }
            for (i=0; i<size; i++) {
                if (stk[i]->lchild) {
                    stk.push_back(stk[i]->lchild);
                }
                if (stk[i]->rchild){
                    stk.push_back(stk[i]->rchild);
                }
            }
            stk.erase(stk.begin(), stk.begin()+size);
        }
        return true;
    }
    
    void test_isSymmetrical2(){
        TreeNode *node4 = new TreeNode(8);
        TreeNode *node2 = new TreeNode(6);
        TreeNode *node7 = new TreeNode(6);
        TreeNode *node1 = new TreeNode(5);
        TreeNode *node3 = new TreeNode(7);
        TreeNode *node6 = new TreeNode(7);
        TreeNode *node9 = new TreeNode(5);
        node4->lchild = node2;
        node4->rchild = node7;
        node2->lchild = node1;
        node2->rchild = node3;
        node7->lchild = node6;
        node7->rchild = node9;
        
        std::cout << "isSymmetrical2 starting......" << std::endl;
        std::cout << isSymmetrical2(node4) << std::endl;
    }
}
#endif /* isSymmetrical_hpp */
