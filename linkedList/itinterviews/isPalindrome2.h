//
//  isPalindrome2.h
//  linkedList
//
//  Created by junl on 2019/11/5.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef isPalindrome2_hpp
#define isPalindrome2_hpp

#include <stdio.h>
#include <stack>
#include "creatlist.h"
/*
 给定一个链表的头节点，请判断该链表是否为回文结构
 
 进阶：
 如果链表长度为N，要求时间复杂度为O(N)，空间复杂度为O(1)
 */

namespace itinterviews {
    //bad
    class isPalindrome1{
    public:
        //思路:利用栈的结构，链表依次进栈，那么出栈的顺序正好是链表从右到左的顺序，如果和链表从左到右的顺序一直的话，那么就是回文的.
        //时间复杂度为O(N)，空间复杂度O(N)
        bool solve(ListNode *head){
            if (!head || !head->next)
                return true;
            ListNode *node = head;
            std::stack<ListNode *> stk;
            while (node) {
                stk.push(node);
                node = node->next;
            }
            node = head;
            while (!stk.empty()) {
                if (stk.top()->val != node->val) {
                    return false;
                }
                stk.pop();
                node = node->next;
            }
            return true;
        }
    };
    
    
    //good
    class isPalindrome2{
    public:
        //思路：反转后半部分的链表，然后一一比较
        //O(N), O(1)
        bool solve(ListNode *head){
            if (!head || !head->next)
                return true;
            
            ListNode *fast,*slow;
            fast = slow = head;
            while (fast && fast->next) {
                fast = fast->next->next;
                slow = slow->next;
            }
            //slow就是后半截的头节点
            ListNode *pre,*ct,*next;
            pre = slow;
            ct = pre->next;
            pre->next = nullptr;
            while (ct) {
                next = ct->next;
                ct->next = pre;
                pre = ct;
                ct = next;
            }
            
            //一一标记,pre为后半截的头节点和head比较
            while (pre && head) {
                if (pre->val != head->val) {
                    return false;
                }
                pre = pre->next;
                head = head->next;
            }
            return true;
        }
    };
    
    
    void test_isPalindrome2(){
        std::cout << "-----判断该链表是否为回文结构-------" << std::endl;
        ListNode *head1 = codinginterviews::creatLists({1,2,1})->next;
        ListNode *head2 = codinginterviews::creatLists({1,2,2,2,1})->next;
        ListNode *head3 = codinginterviews::creatLists({15,6,15})->next;
        ListNode *head4 = codinginterviews::creatLists({1,2,3})->next;
//        class isPalindrome2 so;
        class isPalindrome2 so;
        std::cout << so.solve(head1) << ", " << so.solve(head2) << ", "
        << so.solve(head3) << ", " << so.solve(head4) << std::endl;
    }
}

#endif /* isPalindrome2_hpp */
