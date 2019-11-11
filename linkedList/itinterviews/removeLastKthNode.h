//
//  removeNthFromEnd.h
//  linkedList
//
//  Created by junl on 2019/10/27.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef removeNthFromEnd_hpp
#define removeNthFromEnd_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 分别实现两个函数，一个可以删除单链表中倒数第K个节点，另一个可以删除双链表中倒数等K个节点
 */
namespace itinterviews{
    /*
     思路一:
     快慢指针:假设链表长度为N,我们新增一个占位用的头节点.
     快指针先走k步，那么它只需要再走n-k步就可以到达尾部.这n-k步正好就是倒数第k节点的位置.
     */
    class removeLastKthNode {
    public:
        ListNode* solveInSinglyLL(ListNode *head, int k){
            if (!head || k < 1) return  nullptr;
            ListNode *node = new ListNode(-1);
            node->next = head;
            head = node;
            
            ListNode *knode = node;
            for(int i=0;i<k ;i++){
                if (knode == nullptr) return nullptr;
                knode = knode->next;
            }
            
            node = head;
            while (knode->next) {
                knode=knode->next;
                node=node->next;
            }

            if (node->next) {
                node->next = node->next->next;
            }
            delete node;
            return head->next;
        }
        
        
        ListNode* solveInSinglyLL_v2(ListNode *head, int k){
            if (!head || k < 1) return  nullptr;
            ListNode *node = head;
            while (node) {
                node = node->next;
                k--;
            }
            if (k > 0) {
                return head;
            }else if ( k == 0){
                return head->next;
            }else{
                node = head;
                while (++k != 0 ) {
                    node = node->next;
                }
                if (node->next) {
                    node->next = node->next->next;
                }
                delete node;
                return head;
            }
        }
        
        DoubleNode* solveInDoubleLL(DoubleNode *head, int k){
            if (!head || k < 1) return  nullptr;
            DoubleNode *node = head;
            while (node) {
                node = node->next;
                k--;
            }
            if (k > 0) {
                return head;
            }else if ( k == 0){
                head->next->pre = nullptr;
                return head->next;
            }else{
                node = head;
                while (++k != 0 ) {
                    node = node->next;
                }
                if (node->next) {
                    DoubleNode *next = node->next;
                    node->next = next->next;
                    next->next->pre = node;
                    delete node;
                }
                return head;
            }
        }
    };
    void test_removeLastKthNode(){
        std::cout << "-------删除单链表中倒数第K个节点--------" << std::endl;
        class removeLastKthNode so;
        ListNode *head1 =  codinginterviews::creatLists({1,2,3,4,5})->next;
//        so.solveInSinglyLL(head1, 3)->print();
        so.solveInSinglyLL_v2(head1, 3)->print();
        
        DoubleNode *dhead1 = codinginterviews::creatDoubleLists({1,2,3,4,5})->next;
        so.solveInDoubleLL(dhead1, 3)->print();
    }
};



#endif /* removeNthFromEnd_hpp */
