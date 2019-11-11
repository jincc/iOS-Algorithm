//
//  ReverseLL.h
//  linkedList
//
//  Created by junl on 2019/10/31.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef ReverseLL_hpp
#define ReverseLL_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 分别实现反转单向链表和反转双向链表
 */
namespace itinterviews {
    class ReverseLL{
    public:
        ListNode *solveSL(ListNode *head){
            if (!head || !head->next) {
                return head;
            }
            ListNode *pre,*ct,*next;
            pre = head;
            ct = pre->next;
            pre->next = nullptr;
            while (ct) {
                next = ct->next;
                ct->next = pre;
                pre = ct;
                ct = next;
            }
            return pre;
        };
        
        DoubleNode* solveDL(DoubleNode *head){
            if (!head || !head->next) {
                return head;
            }
            DoubleNode *pre,*ct,*next;
            pre = head;
            ct = pre->next;
            pre->next = nullptr;
            while (ct) {
                next = ct->next;
                ct->next = pre;
                pre->pre = ct;
                pre = ct;
                ct = next;
            }
            pre->pre = nullptr;
            return pre;
        }
    };

    void test_ReverseLL(){
        std::cout << "--------test_ReverseLL---------" << std::endl;
        ListNode *head = codinginterviews::creatLists({1,2,3,4,5})->next;
        head->print();
        class ReverseLL so;
        so.solveSL(head)->print();
        
        DoubleNode *dhead = codinginterviews::creatDoubleLists({1,2,3,4,5})->next;
        dhead->print();
        dhead = so.solveDL(dhead);
        dhead->print();
        
        DoubleNode *tailNode = dhead;
        while (tailNode->next) {
            tailNode = tailNode->next;
        }
        std::cout << "验证双向链表反转过后的pre关系" << std::endl;
        while (tailNode) {
            std::cout << tailNode->val << ", ";
            tailNode = tailNode->pre;
        }
        std::cout << std::endl;
    }
}
#endif /* ReverseLL_hpp */
