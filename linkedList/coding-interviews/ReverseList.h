//
//  ReverseList.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef ReverseList_hpp
#define ReverseList_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 剑指Offer（十五）：反转链表
 输入一个链表，反转链表后，输出新链表的表头。
 https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=13&tqId=11168&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */
namespace codinginterviews {
#pragma mark - 循环实现
    ListNode* ReverseList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;

        ListNode *pNode, *cNode, *nNode;
        pNode = NULL;
        cNode = head;

        while(cNode != NULL){
            nNode = cNode->next;
            cNode->next = pNode;
            pNode = cNode;
            cNode = nNode;
        }
        return pNode;
    }
#pragma mark - 递归实现
    ListNode* ReverseListRecursion(ListNode* head){
        if (head == NULL || head->next == NULL) return head;
        
        ListNode *next = head->next;
        head->next = NULL;
        ListNode *pNode = ReverseListRecursion(next);
        ListNode *newHead = pNode;
        while(pNode->next != NULL){
            pNode = pNode->next;
        }
        pNode->next = head;
        return newHead;
    }
    
    /**
     * Definition for singly-linked list.
     * struct ListNode {
     *     int val;
     *     struct ListNode *next;
     * };
     */

     ListNode* reverseBetween( ListNode* head, int m, int n){
        int pos = 1;
        ListNode *link1 = NULL, *link2=NULL, *ct = head;
        
        for(; ct != NULL && pos < m - 1; pos++, ct = ct->next)
             ;
        if (m != 1) {
             link1 = ct;
             ct = ct->next;pos++;
        }
        link2 = ct;
        ListNode *pre, *next;
        pre = NULL;
        while(ct && pos != n+1){
            next = ct->next;
            ct->next = pre;
            pre = ct;
            ct = next;
            pos++;
        }
        link2->next = ct;
         if (m != 1){
             link1->next = pre;
             return head;
         }
        return pre;
    }

    
    ListNode* partition(ListNode* head, int x){
        ListNode *lHead = NULL, *gHead = NULL, *node = head, *pToDeDelete = NULL, *pre = NULL, *next = NULL;
        while (node) {
            next = node->next;
            if (node->val >= x){
                //删除
                pre->next = node->next;
                if (!gHead) {
                    gHead = pToDeDelete = node;
                }else{
                    pToDeDelete->next = node;
                    pToDeDelete = node;
                }
            }else{
                pre = node;
                if (!lHead) lHead = node;
            }
            node = next;
        }
        if (pToDeDelete)
            pToDeDelete->next = NULL;
        if (pre)
            pre->next = gHead;
        if (lHead)
            return lHead;
        return gHead;
    }
    void test_ReverseList(){
        std::cout << "test_ReverseList staring.......... " << std::endl;
        ListNode *root = creatLists({1,4,3,2,5,2})->next;
        
        root = partition(root, 3);
        root->print();
//        root = ReverseList(root);
//        root->print();
//        root = ReverseListRecursion(root);
//        root->print();
        std::cout << "*******************" << std::endl;
    }
}


#endif /* ReverseList_hpp */
