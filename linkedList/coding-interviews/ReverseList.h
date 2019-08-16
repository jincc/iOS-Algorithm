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
    ListNode* ReverseList(ListNode* pHead) {
        if (!pHead) {
            return nullptr;
        }
        if (!pHead->next) {
            return pHead;
        }
        ListNode *pre,*ct,*next;
        pre = pHead;
        ct = pre->next;
        pre->next = nullptr;
        while (ct) {
            next = ct->next;
            ct->next = pre;
            pre = ct;
            ct = next;
        }
        return pre;
    }
    
    void test_ReverseList(){
        std::cout << "test_ReverseList staring.......... " << std::endl;
        ListNode *root = creatLists({1,2,3,4,5})->next;
        root = ReverseList(root);
        root->print();
    }
}


#endif /* ReverseList_hpp */
