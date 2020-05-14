//
//  HasSubtree.h
//  tree
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef HasSubtree_hpp
#define HasSubtree_hpp

#include <stdio.h>
/*
 剑指Offer（十七）：树的子结构

 输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
https://www.nowcoder.com/practice/6e196c44c7004d15b1610b9afca8bd88?tpId=13&tqId=11170&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
/*
 分析:三种情况:
    1. 当前A和B val一样，需要dfs判断它们的左右子树是不是一样的.
    2. 当前A和B val不一样,判断A的左子树是否包含B
    3. 当前A和B val不一样,判断A的右子树是否包含B
*/
    bool dfs(TreeNode* A, TreeNode* B);
    bool isSubStructure(TreeNode* A, TreeNode* B){
        if (A == NULL || B == NULL) return false;

        return dfs(A, B) || isSubStructure(A->lchild, B) || isSubStructure(A->rchild, B);
    }

    bool dfs(TreeNode* A, TreeNode* B){
        if (B == NULL) return true;
        if (A == NULL) return false;
        if (A->val != B->val) return false;
        return dfs(A->lchild, B->lchild) && dfs(A->rchild, B->rchild);
    }
    
    void test_HasSubtree(){
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
        node6->lchild = new TreeNode(8);
        
        
        TreeNode *pRoot2 = createnode(6);
        pRoot2->lchild = createnode(8);
        
        std::cout << "test_HasSubtree starting........." << std::endl;
        std::cout << isSubStructure(node4, pRoot2) << std::endl;
    }
}
#endif /* HasSubtree_hpp */
