//
//  kthSmallest.h
//  tree
//
//  Created by junlongj on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef kthSmallest_hpp
#define kthSmallest_hpp

#include <stdio.h>
#include <vector>

/*
 230.给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。
 
 说明：
 你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。
 
 示例 1:
 
 输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
 输出: 1
 示例 2:
 
 输入: root = [5,3,6,2,4,null,null,1], k = 3
     5
    / \
   3   6
  / \
 2   4
/
1
 输出: 3
 进阶：
 如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化 kthSmallest 函数？
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
namespace leetcode {
    //直接中序遍历
    int kthSmallest(TreeNode* root, int k) {
        std::vector<TreeNode *> nodes;
        while (!nodes.empty() || root != nullptr) {
            if (root) {
                nodes.push_back(root);
                root = root->lchild;
            }else{
                root = nodes.back();
                nodes.pop_back();
                k--;
                if (k == 0) {
                    return root->val;
                }
                root = root->rchild;
            }
        }
        return 0;
    }
    
    int kthSmallest2(TreeNode* root, int &k) {
        if (root == nullptr) {
            return 0;
        }
        std::cout << root->val << ", " ;
        //先左
        int result = kthSmallest2(root->lchild, k);
        if (k == 0) return result;
        k--;
        if (k == 0) {
            return root->val;
        }
        return kthSmallest2(root->rchild, k);
    }
    
    void test_kthSmallest(){
        TreeNode *root = createnode(5);
        root->lchild = createnode(3);
        root->rchild = createnode(6);
        root->lchild->lchild = createnode(2);
        root->lchild->rchild = createnode(4);
        root->lchild->lchild->lchild = createnode(1);
        
        std::cout << "kthSmallest starting........." << std::endl;
        int no = 3;
        std::cout << kthSmallest2(root, no) << std::endl;
    }
}

#endif /* kthSmallest_hpp */
