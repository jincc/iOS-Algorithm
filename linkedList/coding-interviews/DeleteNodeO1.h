//
//  DeleteNodeO1.h
//  linkedList
//
//  Created by junl on 2020/1/3.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef DeleteNodeO1_hpp
#define DeleteNodeO1_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 面试题13. 在O(1)时间删除链表节点
 
 前提假设：该节点存在链表中.否则查找这个过程就已经o(n)了.
 */
namespace itinterviews {
    void DeleteNodeO1(ListNode **head, ListNode *deleteNode){
        if (!head || !deleteNode)
            return;
        if (deleteNode->next) {
            ListNode *next = deleteNode->next;
            deleteNode->val = next->val;
            deleteNode->next = next->next;
            delete next;
        }else{
            //后置节点不存在
            if (*head == deleteNode){
                delete  deleteNode;
                *head = nullptr;
                deleteNode = nullptr;
            }else{
                ListNode *node = *head;
                while (node->next != deleteNode) {
                    node = node->next;
                }
                node->next = nullptr;
                delete deleteNode;
                deleteNode = nullptr;
            }
        }
    }
}
#endif /* DeleteNodeO1_hpp */
