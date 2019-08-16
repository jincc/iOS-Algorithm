//
//  deleteDuplication.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef deleteDuplication_hpp
#define deleteDuplication_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 剑指Offer（五十六）：删除链表中重复的结点
 在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5


 https://www.nowcoder.com/practice/fc533c45b73a41b0b44ccba763f866ef?tpId=13&tqId=11209&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace codinginterviews {
    ListNode* deleteDuplication(ListNode* pHead){
        if (!pHead) {
            return nullptr;
        }
        if (!pHead->next) {
            return pHead;
        }
        ListNode *head = new ListNode(-1);
        head->next = pHead;
        ListNode *last,*ct;
        last = head;
        ct = last->next;
        while (ct) {
            //每次遍历的时候，判断当前节点和下一个节点是否相等，如果相等的话，找到第一个不等的值.
            if (ct->next && ct->next->val == ct->val) {
                int val = ct->val;
                while (ct && ct->val == val) {
                    ct=ct->next;
                }
                //删除重复节点
                last->next = ct;
            }else{
                //前进一步
                last = ct;
                ct = ct->next;
            }
        }
        return head->next;
    }
    
    void test_deleteDuplication(){
        std::cout << "test_deleteDuplication starting........" << std::endl;
        ListNode *root = creatLists({1,2,3,3,3,4,4,5})->next;
        root = deleteDuplication(root);
        root->print();
    }
}

#endif /* deleteDuplication_hpp */
