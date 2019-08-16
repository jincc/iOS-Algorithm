//
//  mergeTwoLists.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef mergeTwoLists_hpp
#define mergeTwoLists_hpp

#include "singlyLinkedList.h"
#include <iostream>
namespace leetcode {
    /*
     21.Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
     
     Example:
     
     Input: 1->2->4, 1->3->4
     Output: 1->1->2->3->4->4
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/merge-two-sorted-lists
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    ListNode* mergeTwoLists(ListNode *l1, ListNode*l2){
        ListNode *head = new ListNode(0);
        ListNode *ct = head;
        while (l1 && l2) {
            ListNode *node;
            if (l1->val < l2->val) {
                node = l1;
                l1 = l1->next;
            }else{
                node = l2;
                l2 = l2->next;
            }
            ct->next = node;
            ct = node;
        }
        ListNode *lave = l1 ? l1 : l2;
        ct->next = lave;
        return head->next;
    }
    
    ListNode *mergeTwoLists01(ListNode* head1, ListNode* head2){
        ListNode *p1 = head1,  *p2=head2;
        static ListNode dummy(0);
        
        dummy.next = p1;
        ListNode *prev = &dummy;
        
        while(p1 && p2){
            if(p1->val < p2->val){
                prev = p1;
                p1 = p1->next;
            }else{
                prev->next = p2;
                p2 = p2->next;
                prev = prev->next;
                prev->next = p1;
            }
        }
        if (p2){
            prev->next = p2;
        }
        
        return dummy.next;
    }

    
    void test_mergeTwoLists(){
        singlyLinkedList ll,l2;
        ll.insertTail(1);
        ll.insertTail(2);
        ll.insertTail(4);
        
        l2.insertTail(1);
        l2.insertTail(3);
        l2.insertTail(4);
        
        mergeTwoLists01(ll.start(), l2.start())->print();
        
    }
}

#endif /* mergeTwoLists_hpp */
