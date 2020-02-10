//
//  buildTree.h
//  tree
//
//  Created by junl on 2019/8/1.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef buildTree_hpp
#define buildTree_hpp

#include <stdio.h>
#include <vector>
/*
 105.根据一棵树的前序遍历与中序遍历构造二叉树。
 
 注意:
 你可以假设树中没有重复的元素。
 
 例如，给出
 
 前序遍历 preorder = [3,9,20,15,7]
 中序遍历 inorder = [9,3,15,20,7]
 返回如下的二叉树：
 
  3
 / \
 9  20
   /  \
  15   7
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 123456
 */
using namespace std;
namespace leetcode {
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        if (preorder.empty()) {
            return nullptr;
        }
        int start = 0;
        int end = preorder.size();
        int rootValue = preorder[start];
        TreeNode *node = new TreeNode(rootValue);
        if (preorder.size() == 1) {
            return node;
        }
        int i = start;
        while (i<=end && inorder[i] != rootValue) {
            i++;
        }
        if (i == end+1) {
            return node;
        }
        std::vector<int> linorder(inorder.begin(),inorder.begin()+i);
        std::vector<int> lpreoder(preorder.begin()+1,preorder.begin()+1+linorder.size());
        node->lchild = buildTree(lpreoder, linorder);
        std::vector<int> rinorder(inorder.begin()+i+1,inorder.end());
        std::vector<int> rpreoder(preorder.begin()+1+linorder.size(),preorder.end());
        node->rchild = buildTree(rpreoder, rinorder);
        return node;
    }
    TreeNode* reConstructBinaryTree(vector<int> &pre,vector<int> &vin, int pstart,int pend,int vstart, int vend){
        if (pstart>=pre.size() ||
            vstart>=vin.size() ||
            pend>=pre.size()||
            vend>=vin.size() ||
            pstart > pend||
            vstart > vend)
            return nullptr;
        
        int rootValue = pre[pstart];
        TreeNode *node = new TreeNode(rootValue);
        if (pstart - pend == 1)
            return node;
        int findI = vstart;
        while(findI <= vend && vin[findI] != rootValue){
            findI++;
        }
        if (findI == vend+1)
            return node;
        
        int lchildCount = findI - vstart;
        node->lchild = reConstructBinaryTree(pre, vin, pstart+1, pstart+lchildCount, vstart, findI-1);
        node->rchild = reConstructBinaryTree(pre, vin, pstart+1+lchildCount, pend, findI+1, vend);
        return node;
    }
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        //前序遍历，跟左右
        //中序遍历，左跟右
        if (pre.size() != vin.size() || pre.empty())
            return nullptr;
        return reConstructBinaryTree(pre, vin, 0, pre.size()-1, 0, vin.size()-1);
    }

    
    void test_buildTree(){
        std::cout << "build tree starting......." <<std::endl;;
        std::vector<int> preorder{1,2,3,4,5,6,7};
        std::vector<int> inorder{3,2,4,1,6,5,7};
//        TreeNode *root =  buildTree(preorder, inorder);
        TreeNode *root = reConstructBinaryTree(preorder, inorder);
        btree::levelOrder(root);
    }
    
}
#endif /* buildTree_hpp */
