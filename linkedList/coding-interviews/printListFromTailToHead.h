//
//  printListFromTailToHead.h
//  linkedList
//
//  Created by junl on 2019/8/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef printListFromTailToHead_hpp
#define printListFromTailToHead_hpp

#include <stdio.h>
#include <vector>

/*
 剑指Offer（三）：从尾到头打印链表:
 输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。
 https://www.nowcoder.com/practice/d0267f7f55b3412ba93bd35cfa8e8035?tpId=13&tqId=11156&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking

 */


namespace codinginterviews {
    std::vector<int> printListFromTailToHead(ListNode* head) {
        if (head == nullptr) {
            return {};
        }
        std::vector<ListNode *> nodes;
        std::vector<int> values;
        ListNode *node = head;
        while (node) {
            nodes.push_back(node);
            node = node->next;
        }
        for (int i=nodes.size()-1; i>=0; i--) {
            values.push_back(nodes[i]->val);
        }
        return values;
    }
    
    void test_printListFromTailToHead(){
        
    }
}
#endif /* printListFromTailToHead_hpp */
