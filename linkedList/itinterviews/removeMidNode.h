//
//  removeMidNode.h
//  linkedList
//
//  Created by junl on 2019/10/28.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef removeMidNode_hpp
#define removeMidNode_hpp

#include <stdio.h>
#include "creatlist.h"

namespace itinterviews {
    /*
     删除链表的中间节点
     */
    class removeMidNode{
    public:
        /*
         利用快慢指针，快指针走到末尾的时候，慢指针正好走到一半，lastSlow是它之前的那个节点
         */
        ListNode *solve_bad(ListNode *head){
            if (!head || !head->next) {
                return head;
            }
            ListNode *fast,*slow,*lastSlow;
            fast = head;
            slow = head;
            lastSlow = nullptr;
            while (fast && fast->next && fast->next->next) {
                fast = fast->next->next;
                lastSlow = slow;
                slow = slow->next;
            }
            //说明1个或2个节点
            if (lastSlow == nullptr) {
                return head->next;
            }
            if (lastSlow->next) {
                lastSlow->next = lastSlow->next->next;
            }
            return head;
        }
        /*
         思路:
         当链表长度为3时，删除第2个节点
         当链表长度为4时，删除第2个节点
         当链表长度为5时，删除第3个节点
         当链表长度为6时，删除第3个节点
         
         就是说链表长度每增加2，删除的位置前进1步.
         */
        ListNode *solve(ListNode *head){
            if (!head || !head->next) {
                return head;
            }
            if (!head->next->next) {
                return head->next;
            }
            ListNode *fast,*slow;
            //我们先让快指针先走一步，然后fast和slow在一起向前移，这样slow最终的位置正好是中节点的前一个位置
            fast = head->next->next;
            slow = head;
            
            while (fast->next && fast->next->next) {
                fast = fast->next->next;
                slow = slow->next;
            }
            if (slow->next) {
                slow->next = slow->next->next;
            }
            return head;
        }
    };
    
    void test_removeMidNode(){
        std::cout << "------删除链表中间节点-----" << std::endl;
        ListNode *head1 =  codinginterviews::creatLists({1,2})->next;
        class removeMidNode so;
        so.solve(head1)->print();
    }
}

#endif /* removeMidNode_hpp */
