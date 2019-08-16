//
//  btree.h
//  tree
//
//  Created by junl on 2019/7/20.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef btree_hpp
#define btree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
template <typename T>
class bnode{
public:
    T val;
    bnode *lchild;
    bnode *rchild;
    bnode(const T &val_):val(val_),lchild(nullptr),rchild(nullptr){}
    void print(){
        std::cout << "val: " << val << ", isleaf: " << (lchild==nullptr && rchild == nullptr) << std::endl;
    }
};


typedef bnode<int> TreeNode;

#define createnode(value)  new TreeNode(value)

/*
 二叉树的每个节点最多有两个子节点，分别是左子节点和右子节点，有两种特殊的树，分别是满二叉树和完全二叉树。满二叉树指的是除了子节点以外，其余每个节点都有两个子节点。完全二叉树指的是一种可以借助数组来存储的二叉树。如下：
 
 ![IMAGE](quiver-image-url/CDA8E95ED689E72D63570CE80F5F9975.jpg =1142x604)
 
 其他二叉树一般都是利用链式存储法来储存的，因为用数组来存储的话会比较浪费空间。
 
 需要重点掌握的:
 
 1. 前序中序后序变量
 2. 根节点，叶子节点，父节点，子节点，深度，高度等概念
 3. 层级遍历
 

 */
namespace btree {
    //先结点的值，在左子树，在右子树
    template <typename T>
    void preOrder(bnode<T> *root){
        if (!root) {
            return;
        }
        root->print();
        preOrder(root->lchild);
        preOrder(root->rchild);
    }
    
    template <typename T>
    void inOrder(bnode<T> *root){
        if (!root) {
            return;
        }
        inOrder(root->lchild);
        root->print();
        inOrder(root->rchild);
    }
    
    template <typename T>
    void postOrder(bnode<T> *root){
        if (!root) {
            return;
        }
        postOrder(root->lchild);
        postOrder(root->rchild);
        root->print();
    }
    
    template <typename T>
    void levelOrder(bnode<T> *root){
        std::vector<bnode<T> *> vecs;
        vecs.push_back(root);
        while (!vecs.empty()) {
            //先把每一层打印完，在把下一层的元素加入进来.
            size_t size = vecs.size();
            for (int i=0;i<size;i++){
                auto &x = vecs[i];
                x->print();
                if (x->lchild){
                    vecs.push_back(x->lchild);
                }
                if (x->rchild){
                    vecs.push_back(x->rchild);
                }
            }
            vecs.erase(vecs.begin(), vecs.begin()+size);
        }
    }
    
    /*打印叶子节点*/
    template <typename T>
    void printfleaf(bnode<T> *root){
        if (!root)
            return;
        if (root->lchild == nullptr && root->rchild == nullptr) {
            root->print();
        }else{
            printfleaf(root->lchild);
            printfleaf(root->rchild);
        }
    }
    
    /*获取叶子节点的数量*/
    template <typename T>
    int getleafnum(bnode<T> *root){
        if (!root)
            return 0;
        if (root->lchild == nullptr && root->rchild == nullptr) {
            return 1;
        }else{
            return getleafnum(root->lchild) + getleafnum(root->rchild);
        }
    }
    
    /*打印树的高度*/
    template <typename T>
    int getheight(bnode<T> *root){
        if (!root ) {
            return 0;
        }
        if (root->lchild == nullptr && root->rchild == nullptr) {
            return 0;
        }
        return std::max(getheight(root->lchild) , getheight(root->rchild)) + 1;
    }
}


#endif /* btree_hpp */
