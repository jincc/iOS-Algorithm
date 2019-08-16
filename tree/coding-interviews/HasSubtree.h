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
     思路是递归查找
     
     如果pRoot1.val == pRoot2.val，则说明根节点匹配，继续判断pRoot1.left是否包含pRoot2.left 和 pRoot1.right是否包含pRoot2.right
     如果pRoot1.val != pRoot2.val，则说明根节点不匹配，那么要么pRoot2存在于左子树，要么存在于右子树.
     需要注意终止条件.
     */
    bool HasSubtree2(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (pRoot2 == nullptr) {//如果pRoot2为空，说明肯定是包含关系
            return true;
        }
        if (pRoot1 == nullptr && pRoot2 != nullptr) {//如果pRoot1已经没有节点了，但是pRoot2还存在值，那么肯定不是包含关系.
            return false;
        }
        if (pRoot1->val == pRoot2->val &&
            HasSubtree2(pRoot1->lchild, pRoot2->lchild) &&
            HasSubtree2(pRoot1->rchild, pRoot2->rchild)) {
            return true;
        }
        return HasSubtree2(pRoot1->lchild, pRoot2) || HasSubtree2(pRoot1->rchild, pRoot2);
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (pRoot2 == nullptr) {
            return false;
        }
        return HasSubtree2(pRoot1, pRoot2);
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
        std::cout << HasSubtree(node4, pRoot2) << std::endl;
    }
}
#endif /* HasSubtree_hpp */
