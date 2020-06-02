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
    void dfs(TreeNode *root, int sum, int &ctsum, vector<vector<int>> &result, vector<int> &path){
        if (!root) return;
        ctsum += root->val;
        path.push_back(root->val);
        if (root->lchild == NULL && root->rchild == NULL && ctsum == sum){
            result.push_back(path);//这里不能直接return，因为后面需要执行回滚节点逻辑.
        }
        if (root->lchild){
            dfs(root->lchild, sum, ctsum, result, path);
        }
        if (root->rchild){
            dfs(root->rchild, sum, ctsum, result, path);
        }
        ctsum -= root->val;
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        if (root == NULL) return result;
        vector<int> path;
        int ctsum = 0;
        dfs(root, sum, ctsum, result, path);
        return result;
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
        
        pathSum(node4, 7);
    }
}
#endif /* FindPath_hpp */
