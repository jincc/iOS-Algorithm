//
//  Tree.h
//  tree
//
//  Created by junl on 2020/5/13.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct BTreeNode  BTreeNode;
    struct BTreeNode{
        int val;
        BTreeNode *left;
        BTreeNode *right;
    };
    BTreeNode *creatTreeNode(int val);
    BTreeNode *creatTree(int vals[], int n);
    void preOrder(BTreeNode *pTree);
    void preOrderIterate(BTreeNode *pTree);
    void inOrder(BTreeNode *pTree);
    void inOrderIterate(BTreeNode *pTree);
    void postOrder(BTreeNode *pTree);
    void postOrderIterate(BTreeNode *pTree);
    void levelOrder(BTreeNode *pTree);
    
    //根据前序遍历和中序遍历构建二叉树
    BTreeNode *construct(int preorder[], int inorder[], int size);
#ifdef __cplusplus
}
#endif

#endif /* Tree_h */
