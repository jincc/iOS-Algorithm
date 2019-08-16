//
//  FindPath.h
//  tree
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FindPath_hpp
#define FindPath_hpp

#include <stdio.h>

/*
 剑指Offer（二十四）：二叉树中和为某一值的路径
 输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)
https://www.nowcoder.com/practice/b736e784e3e34731af99065031301bca?tpId=13&tqId=11177&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2
 
 */


namespace codinginterviews {
    std::vector<std::vector<int> >  Findpaths;
    /*
     思路：用个递归来实现，先序遍历，深度访问
     * 每次访问一个节点，那么就将当前权值求和
     * 如果当前权值和与期待的和一致，那么说明我们找到了一个路径，保存或者输出
     * 否则的话就递归其左右孩子节点
     */
    void FindPath(TreeNode* root,int expectNumber, std::vector<int> r) {
        if (!root) {
            return;
        }
        std::cout << root->val << std::endl;
        r.push_back(root->val);
        //如果叶子节点满足条件，则r满足
        if (root->lchild == nullptr && root->rchild == nullptr && root->val == expectNumber) {
            Findpaths.push_back(r);
            return;
        }
        //否则在左子树或右子树上查找,这里需要注意的是，权重值和r路径数组是作为参数存在的，所以它们会自动恢复，所以不需要清空r
        if (root->lchild) {
            FindPath(root->lchild, expectNumber-root->val, r);
        }
        if (root->rchild) {
            FindPath(root->rchild, expectNumber-root->val, r);
        }
    }
    std::vector<std::vector<int> > FindPath(TreeNode* root,int expectNumber) {
        std::vector<int> r;
        FindPath(root, expectNumber, r);
        return Findpaths;
    }
    
    void test_FindPath(){
        std::cout << "test_FindPath starting........" << std::endl;
        TreeNode *node4 = new TreeNode(1);
        TreeNode *node2 = new TreeNode(2);
        TreeNode *node7 = new TreeNode(3);
        TreeNode *node1 = new TreeNode(4);
        TreeNode *node3 = new TreeNode(5);
        TreeNode *node6 = new TreeNode(3);
        TreeNode *node9 = new TreeNode(6);
        node4->lchild = node2;
        node4->rchild = node7;
        node2->lchild = node1;
        node2->rchild = node3;
        node7->lchild = node6;
        node7->rchild = node9;
        
        FindPath(node4, 7);
    }
}
#endif /* FindPath_hpp */
