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
    
    void test_ReverseList(){
        std::cout << "test_ReverseList staring.......... " << std::endl;
        ListNode *root = creatLists({1,2,3,4,5})->next;
        root = ReverseList(root);
        root->print();
        root = ReverseListRecursion(root);
        root->print();
        std::cout << "*******************" << std::endl;
    }
}


#endif /* ReverseList_hpp */
