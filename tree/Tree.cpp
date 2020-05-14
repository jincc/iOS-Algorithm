//
//  Tree.c
//  tree
//
//  Created by junl on 2020/5/13.
//  Copyright © 2020 junl. All rights reserved.
//

#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#pragma mark - 遍历
void preOrder(BTreeNode *pTree){
    if (pTree == NULL) return;
    printf("%d\t", pTree->val);
    preOrder(pTree->left);
    preOrder(pTree->right);
}
void inOrder(BTreeNode *pTree){
    if (pTree == NULL) return;
    inOrder(pTree->left);
    printf("%d\t", pTree->val);
    inOrder(pTree->right);
}
void postOrder(BTreeNode *pTree){
    if (pTree == NULL) return;
    postOrder(pTree->left);
    postOrder(pTree->right);
    printf("%d\t", pTree->val);
}

void preOrderIterate(BTreeNode *pTree){
    if (pTree == NULL) return;

    std::stack<BTreeNode *> stk;
    stk.push(pTree);
    while(!stk.empty()){
        BTreeNode *node = stk.top();
        stk.pop();
        printf("%d\t", node->val);
        if (node->right)
            stk.push(node->right);
        if (node->left)
            stk.push(node->left);
    }
}
void inOrderIterate(BTreeNode *pTree){
    if (pTree == NULL) return;
    //左跟右
    
    std::stack<BTreeNode *> stk;
    while(!stk.empty() || pTree != NULL){
        if (pTree){
            stk.push(pTree);
            pTree = pTree->left;
        }else{
            BTreeNode *node = stk.top();
            stk.pop();
            printf("%d\t",node->val);
            if (node->right){
                pTree = node->right;
            }
        }
    }
}

void postOrderIterate(BTreeNode *pTree){
    if (pTree == NULL) return;
    //左右跟
    
    std::stack<BTreeNode *> stk;
    std::stack<BTreeNode *> res;
    stk.push(pTree);
    while(!stk.empty()){
        BTreeNode *top = stk.top();
        stk.pop();
        res.push(top);
        if (top->left){
            stk.push(top->left);
        }
        if (top->right){
            stk.push(top->right);
        }
    }
    
    while(!res.empty()){
        BTreeNode *top = res.top();
        res.pop();
        printf("%d\t", top->val);
    }
}

void levelOrder(BTreeNode *pTree){
    if (pTree == NULL) return;
    
    int i;
    std::queue<BTreeNode *> queue;
    queue.push(pTree);
    while (!queue.empty()) {
        size_t size = queue.size();
        for(i=0; i < size; i++) {
            BTreeNode *front = queue.front();
            queue.pop();
            printf("%d\t",front->val);
            if (front->left)
                queue.push(front->left);
            if (front->right)
                queue.push(front->right);
        }
    }
}
#pragma mark - 创建
BTreeNode *creatTreeNode(int val){
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}
BTreeNode *creatTree(int vals[], int n){
    int i = 0;
    BTreeNode *tree = NULL;
    BTreeNode *p = NULL;
    std::queue<BTreeNode *> queue;
    while(i < n){
        if (tree == NULL){
            p = tree = creatTreeNode(vals[i++]);
        }else{
            p->left = creatTreeNode(vals[i++]);
            p->right = creatTreeNode(vals[i++]);
            queue.push(p->left);
            queue.push(p->right);
            p = queue.front();
            queue.pop();
        }
    }
    return tree;
}

#pragma mark - sword
BTreeNode *construct(int preorder[], int inorder[], int size){
    if (size == 0) return NULL;
    int rootval =  preorder[0];
    BTreeNode *pRoot = (BTreeNode *)malloc(sizeof(BTreeNode));
    pRoot->val = rootval;
    pRoot->left = pRoot->right = NULL;
    if (size == 1) return pRoot;
    //构建左右子树
    int i;
    
    for (i = 0; i < size; i++){
        if (inorder[i] == rootval){
            break;
        }
    }
    if (i == size) return pRoot;//error
    pRoot->left = construct(preorder+1, inorder, i);
    pRoot->right = construct(preorder+i+1, inorder+i+1, size - i - 1);
    return pRoot;
}
