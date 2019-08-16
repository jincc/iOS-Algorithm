//
//  reverseList.h
//  linkedList
//
//  Created by junl on 2019/7/17.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef reverseList_hpp
#define reverseList_hpp

#include <stdio.h>
#include "singlyLinkedList.h"

namespace leetcode {
    /*
     206.反转一个单链表。
     
     示例:
     
     输入: 1->2->3->4->5->NULL
     输出: 5->4->3->2->1->NULL
     */
    ListNode* reverseList(ListNode* head) {
        ListNode *pre,*ct,*next;
        if (!head->next) {
            return head;
        }

        
        ct = head;
        pre = nullptr;
        while (ct) {
            next = ct->next;
            ct->next = pre;
            pre = ct;
            ct = next;
        }
        return pre;
        
    }
    
    void test_reverseList(){
        singlyLinkedList ll;
        ll.insertTail(3);
        ll.insertTail(2);
        ll.insertTail(0);
        ll.insertTail(-4);
        reverseList(ll.start())->print();
    }
}



#endif /* reverseList_hpp */
