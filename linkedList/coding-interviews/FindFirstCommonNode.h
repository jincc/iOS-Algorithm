//
//  FindFirstCommonNode.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef FindFirstCommonNode_hpp
#define FindFirstCommonNode_hpp

#include <stdio.h>

/*
 剑指Offer（三十六）：两个链表的第一个公共结点
 输入两个链表，找出它们的第一个公共结点。
https://www.nowcoder.com/practice/6ab1d9a29e88450685099d45c9e31e46?tpId=13&tqId=11189&tPage=2&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking
 */

namespace codinginterviews {
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if (pHead1 == nullptr || pHead2 == nullptr) {
            return nullptr;
        }
        int size1=0,size2=0;
        ListNode *ct1 = pHead1;
        while (ct1) {
            size1++;
            ct1=ct1->next;
        }
        ListNode *ct2 = pHead2;
        while (ct2) {
            size2++;
            ct2=ct2->next;
        }
        //链表长的先多走几步，这样他们到末尾的距离是一样的
        ListNode *fast = size1 < size2 ? pHead2 : pHead1;
        ListNode *slow = fast == pHead2 ? pHead1 : pHead2;
        int i=0;
        while (i<abs(size1-size2)) {
            fast = fast->next;
            i++;
        }
        while (fast && slow) {
            if (fast == slow) {
                return fast;
            }
            fast = fast->next;
            slow = slow->next;
        }

        return nullptr;
    }
}
#endif /* FindFirstCommonNode_hpp */
