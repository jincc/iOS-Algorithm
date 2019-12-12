//
//  reverseKNodes.h
//  linkedList
//
//  Created by junl on 2019/11/27.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef reverseKNodes_hpp
#define reverseKNodes_hpp

#include <stdio.h>
#include "creatlist.h"
#include <stack>
/*
 将单链表的每K个节点之间逆序
 给定一个单链表的头节点head，实现一个调整单链表的函数，使得每ke个节点之间逆序，如果不够K个节点，则不调整最后一个节点.
 比如:
 1->2->3->4->5->6->7->8  k=3
 
 3->2->1->6->5->4->7->8
 
 */

namespace itinterviews {
    /*
     利用栈的结构
     利用计步器，一直入栈，直到cnt == k:
        1. 第一种情况，stk{1,2,3},这个时候翻转后，需要链接1和4
        2. 第二种情况,3->2->1->4->5->6->7->8, stk{4,5,6}，翻转后需要链接4和7,也要链接1和4
     */
    class reverseKNodes_stack{
    public:
        ListNode *solve(ListNode *head, int k){
            if (!head || k <= 1)
                return head;
            ListNode *newHead = nullptr;
            ListNode *ct = head;
            ListNode *sortLast = nullptr;
            int cnt = 0;
            std::stack<ListNode *> stk;
            while (ct) {
                if (cnt++ == k) {
                    cnt = 0;
                    if (newHead == nullptr){
                        newHead = stk.top();
                    }else{
                        //连接上一次翻转和这一次将翻转的
                        sortLast->next = stk.top();
                    }
                    //翻转
                    ListNode *ct2 = stk.top();
                    stk.pop();
                    while (!stk.empty()) {
                        ct2->next = stk.top();
                        ct2 = stk.top();
                        stk.pop();
                    }
                    /*
                     现在的链表有两截:
                     已经翻转过的3，2，1
                     还未翻转的4,5,6,7,8
                     连接已经翻转的部分和后面还没处理的链表
                     */
                    sortLast = ct2;
                    ct2->next = ct;
                }else{
                    stk.push(ct);
                    ct = ct->next;
                }
            }
            return newHead ?: head;
        }
        
    };
    
    /*
     通过上面的解法，关键点在于如何链接待倒序部分和之前的部分，以及倒序部分和之后的部分.
     */
    class reverseKNodes{
    public:
        ListNode *solve(ListNode *head, int k){
            if (!head || k <= 1)
                return head;
            ListNode *newHead = nullptr;
            ListNode *start, *next, *ct, *pre;
            start = next = pre =  nullptr;
            ct = head;
            
            int cnt = 1;
            while (ct!=nullptr) {
                next = ct->next;
                if (cnt == k){
                    //倒序然后链接前后部分
                    
                    
                    start =  pre == nullptr ? head : pre->next;
                    newHead = newHead == nullptr ? ct : newHead;
                    reverseAndLink(pre, next,start,ct);
                    pre = start;
                    cnt = 0;
                }
                cnt++;
                ct = next;
            }
            return newHead;
        }
        
        void reverseAndLink(ListNode *left, ListNode *right, ListNode *start, ListNode *end){
            ListNode *pre = start;
            ListNode *ct = pre->next;
            ListNode *next = nullptr;
            pre->next = nullptr;
            while (ct != right) {
                next = ct->next;
                ct->next = pre;
                pre = ct;
                ct = next;
            }
            
            if (left != nullptr){
                left ->next = end;
            }
            start->next = right;
        }
    };
    
    void test_reverseKNodes(){
        std::cout << "---------将单链表的每K个节点之间逆序--------" <<std::endl;
        class reverseKNodes so;
        ListNode *Head  = codinginterviews::creatLists({1,2,3,4,5,6,7,8})->next;
        so.solve(Head, 3)->print();
    }
}

#endif /* reverseKNodes_hpp */
