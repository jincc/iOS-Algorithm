//
//  FindKthToTail.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FindKthToTail_hpp
#define FindKthToTail_hpp

#include <stdio.h>
#include "creatlist.h"
/*
 剑指Offer（十四）：链表中倒数第k个结点
 输入一个链表，输出该链表中倒数第k个结点。
 https://www.nowcoder.com/practice/529d3ae5a407492994ad2a246518148a?tpId=13&tqId=11167&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 */

namespace codinginterviews {
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        //利用快慢指针
        ListNode *head = new ListNode(0);
        head->next = pListHead;
        int i=0;
        ListNode *fast,*slow;
        fast = slow = head;
        while (fast && i++<k) {
            fast = fast->next;
        }
        if (fast == nullptr) {
            return nullptr;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
    
    void test_FindKthToTail(){
        std::vector<int> nos{};
        ListNode *root = creatLists(nos)->next;
        ListNode *node = FindKthToTail(root, 100);
        
        std::cout << "test_FindKthToTail starting....... " << std::endl;
        node->print();
    }
}
#endif /* FindKthToTail_hpp */
