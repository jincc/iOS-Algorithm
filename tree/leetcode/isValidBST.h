//
//  isValidBST.h
//  tree
//
//  Created by junl on 2019/7/30.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isValidBST_hpp
#define isValidBST_hpp

#include <stdio.h>
#include <stack>
/*
 98.给定一个二叉树，判断其是否是一个有效的二叉搜索树。
 
 假设一个二叉搜索树具有如下特征：
 
 节点的左子树只包含小于当前节点的数。
 节点的右子树只包含大于当前节点的数。
 所有左子树和右子树自身必须也是二叉搜索树。
 示例 1:
 
 输入:
   2
  / \
 1   3
 输出: true
 示例 2:
 
 输入:
  5
 / \
 1  4
   / \
  3   6
 输出: false
 解释: 输入为: [5,1,4,null,null,3,6]。
      根节点的值为 5 ，但是其右子节点值为 4 。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/validate-binary-search-tree
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

namespace leetcode {
    
#pragma mark - 方法一:递归
    /*
     方法一:
     注意二叉搜索树的定义，整个右子树的所有节点都比根节点大，整个左子树的所有节点都比根节点小。而不应该仅仅比较节点和左节点右节点的关系.
     
     所有,我们应该定义两个边界值，里面存储的是每个二叉搜索树的根节点
     */
#define NOT_FOUNT INT_MAX
    bool isValidBST(TreeNode* root,int lower, int up) {
        if (!root) {
            return true;
        }
        int val = root->val;
        if (up != NOT_FOUNT && val >= up) {
            return false;
        }
        if (lower != NOT_FOUNT && val <= lower){
            return false;
        }
        return isValidBST(root->lchild, lower, val) && //左子树的值都应该小于val
        isValidBST(root->rchild, val, up); //右子树的值都应该大于val
    }
    bool isValidBST(TreeNode* root){
        return isValidBST(root, NOT_FOUNT, NOT_FOUNT);
    }
    
#pragma mark - 方法二:中序遍历
    /*
     中序遍历，每个元素的值都比后面元素的值小，通过这一点来判断是否是二叉搜索树.
     */
    bool isValidBST2(TreeNode* root){
        std::stack<TreeNode* >stk;
        std::vector<int> inorders;
        while (!stk.empty() || root != nullptr) {
            //先将所有根和左节点入栈，栈的顶部为叶子节点。
            if (root) {
                stk.push(root);
                root = root->lchild;
            }else{
                TreeNode *top =  stk.top();
                stk.pop();
                //判断当前的值和中序上一个节点的值的关系
                inorders.push_back(top->val);
                //如果存在右子树，轮训
                root = top->rchild;
            }
        }
        
        for (int i=0;inorders.size() && i<inorders.size()-1;i++){
            if (inorders[i]>=inorders[i+1]) {
                return false;
            }
        }
        return true;
    }
    
    void test_isValidBST(){
        TreeNode *root5 = new TreeNode(2);
        TreeNode *node1 = new TreeNode(1);
        TreeNode *node4 = new TreeNode(3);
//        TreeNode *node3 = new TreeNode(3);
//        TreeNode *node6 = new TreeNode(6);
        root5->lchild = node1;
        root5->rchild = node4;
//        node4->lchild = node3;
//        node4->rchild = node6;
        std::cout << "验证二叉搜索树  starting.........." << std::endl;
        std::cout << isValidBST2(root5) << std::endl;
    }
}
#endif /* isValidBST_hpp */
