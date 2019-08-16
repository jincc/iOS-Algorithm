//
//  GetNext.h
//  tree
//
//  Created by junlongj on 2019/8/3.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef GetNext_hpp
#define GetNext_hpp

#include <stdio.h>

/*
 剑指Offer（五十七）：二叉树的下一个结点
 
 给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
https://www.nowcoder.com/practice/9023a0c988684a53960365b889ceaf5e?tpId=13&tqId=11210&tPage=3&rp=2&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */
namespace codinginterviews {
    struct TreeLinkNode {
        int val;
        struct TreeLinkNode *left;
        struct TreeLinkNode *right;
        struct TreeLinkNode *next;
        TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
            
        }
    };
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if (pNode == nullptr) {
            return nullptr;
        }
        //如果当前节点存在右子树，那么结果是右子树的最左那个节点
        if (pNode->right != nullptr) {
            TreeLinkNode *ct = pNode->right;
            while (ct && ct->left) {
                ct = ct->left;
            }
            return ct;
        }else if (pNode->next != nullptr){
            //如果当前节点没有右子树，那么就要分几种情况了.
            //如果当前节点是其父节点的左节点的话，那么下一个就为其父节点。
            //如果当前节点是其父节点的右字节的话，需要找到整个左子树的根节点。
            if (pNode->next->left == pNode) {
                return pNode->next;
            }else{
                TreeLinkNode *ct = pNode->next;
                //一直找到它的父节点是左节点的情况
                while (ct->next && ct->next->left != ct) {
                    ct = ct->next;
                }
                if (ct) {
                    return ct->next;
                }
                return nullptr;
            }
        }
        return nullptr;
    }
}
#endif /* GetNext_hpp */
