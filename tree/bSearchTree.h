//
//  bSearchTree.h
//  tree
//
//  Created by junl on 2019/7/22.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bSearchTree_hpp
#define bSearchTree_hpp

#include <stdio.h>
#include <vector>
#include "btree.h"
/*
 二分查找树
 二叉查找树是为了实现快速查找而生的，除此之外，还支持快速插入，快速查找。
 
 二叉查找树之所以能够实现快速查找，删除，插入，主要是依赖于它自身的结构。<font size=5 color=red>二叉查找树要求，在树中的任意节点，其左子树上的每一个节点的值都要小于这个节点的值，而右子树节点的值都大于这个节点的值
 
 
 二叉查找树的性能(增删改)跟树的高度成正比。两个极端情况下的时间复杂度为o(n)和o(logn)，分别对应二叉树退化为链表和完全二叉树。
 */

namespace bSearchTree{
    typedef bnode<int> inode;
    /**
     发现节点
     */
    bool find_node(int val, inode *tree){
        if (tree == nullptr) {
            return false;
        }
        if (tree->val == val) {
            return true;
        }else if (tree->val < val){
            return find_node(val, tree->rchild);
        }else{
            return find_node(val, tree->lchild);
        }
    }
    /**
     插入节点
     */
    void insert_node(int val,inode *tree){
        if (tree->val < val) {
            //在右子树
            if (tree->rchild == nullptr) {
                tree->rchild = new inode(val);
                return;
            }
            insert_node(val, tree->rchild);
        }else{
            //在左子树
            if (tree->lchild == nullptr) {
                tree->lchild = new inode(val);
                return;
            }
            insert_node(val, tree->lchild);
        }
    }
    
    /**
     删除节点
     */
    void delete_node(int val,inode *tree){
        /*
        //step1.找到要删除的节点
        //step2.判断要删除的节点的情况:
            1. 叶子节点
            2. 只有一个子节点
            3. 有两个子节点
        */
        
        inode *ct, *parent;
        ct = tree;
        parent = nullptr;
        while (ct && ct->val != val) {
            parent = ct;
            if (ct->val < val) {
                ct = ct->rchild;
            }else{
                ct = ct->lchild;
            }
        }
        if (ct ==nullptr) {
            return;
        }
        if (ct->lchild && ct->rchild){
            //两个子节点都存在
            //找到右子树最小的节点，把它设为新的父节点
            inode *min = ct->rchild;
            inode *minFather = ct;
            while (min->lchild) {
                minFather = min;
                min = min->lchild;
            }
            ct->val = min->val;
            ct = min;
            parent = minFather;
        }
        inode *child = ct->lchild ? ct->lchild : ct->rchild;
        if (parent == nullptr) {
            tree = child;
            return;
        }
        if (parent->lchild == ct) {
            parent->lchild = child;
        }else{
            parent->rchild = child;
        }
    }
    
    /**
     获取节点里面最大的值
     */
    int get_max(inode *tree){
        inode *ct = tree;
        while (ct->rchild) {
            ct = ct->rchild;
        }
        return ct->val;
    }
    
    /**
     获取节点里面最小的值
     */
    int get_min(inode *tree){
        inode *ct = tree;
        while (ct->lchild) {
            ct = ct->lchild;
        }
        return ct->val;
    }
    
    /**
     获取前置节点
     */
    int get_prenode(int val, inode *tree){
        
        inode *ct,*pre;
        ct = tree;
        pre = nullptr;
        while (ct) {
            if (ct->val < val ) {
                pre = ct;
                ct = ct->rchild;
            }else if ( ct->val > val){
                pre = ct ;
                ct = ct->lchild;
            }else{
                break;
            }
        }
        return (ct == nullptr) ? -1 : pre->val;
    }
    
    /**
     获取后置节点
     */
    int get_postnode(int val, inode *tree){
        inode *ct;
        ct = tree;
        while (ct) {
            if (ct->val < val ) {
                ct = ct->rchild;
            }else if ( ct->val > val){
                ct = ct->lchild;
            }else{
                break;
            }
        }
        if (ct == nullptr) {
            return -1;
        }else if (ct->lchild){
            return ct->lchild->val;
        }else{
            return ct->rchild->val;
        }
    }
}

#endif /* bSearchTree_hpp */
